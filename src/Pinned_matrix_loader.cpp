/*
 * Pinnedmatrixloader.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: ninaavr
 */

#include "Pinned_matrix_loader.h"

Pinned_matrix_loader::Pinned_matrix_loader() {
	// TODO Auto-generated constructor stub

}

Pinned_matrix_loader::~Pinned_matrix_loader() {
	// TODO Auto-generated destructor stub
}

void Pinned_matrix_loader::load_M(TexturedPolyhedron& tp, Halfedges& pinnedVertices, Eigen::SparseMatrix<double>& M){

}

void Pinned_matrix_loader::load_vertex_in_M(Halfedge_handle h, Eigen::SparseMatrix<double>& M){




	K::Point_2 facedim2[3];
	Facet_handle face = h->facet();
	mc.project_triangle(face, facedim2);
	double sqrt_f_dt = sqrt(mc.calc_dt(facedim2));
	Vertex_handle v = h->vertex();
	int col;
	col = column[v].first;
	//first vertex in the face
	M.insert (row[face], col) = mc.calc_W(face, v, true) / sqrt_f_dt;
	M.insert (row[face] + row.size(), col) = mc.calc_W(face, v, false) / sqrt_f_dt;
	//second vertex in the face
	face = h ->opposite()->facet();
	mc.project_triangle(face, facedim2);
	sqrt_f_dt = sqrt(mc.calc_dt(facedim2));
	col = column[v].first;
	M.insert (row[face], col) = mc.calc_W(face, v, true) / sqrt_f_dt;
	M.insert (row[face] + row.size(), col) = mc.calc_W(face, v, false) / sqrt_f_dt;
}

