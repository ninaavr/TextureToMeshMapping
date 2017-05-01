/*
 * Pinnedmatrixloader.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: ninaavr
 */

#include "Pinned_matrix_loader.h"

using namespace Eigen;

Pinned_matrix_loader::Pinned_matrix_loader() {
}

Pinned_matrix_loader::~Pinned_matrix_loader() {
}

void Pinned_matrix_loader::load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M){
	//if(pinnedVertices.size()<2){
	//	cout << "pinned Vertices must be at least 2!!" << endl;
	//	exit(-1);
	//}
	set_tags(tp);
	set_columns(tp);
	set_rows(tp);
	int sizeColumns = count_this_type();
	M = SparseMatrix<double>(2 * tp.size_of_facets(), 2*sizeColumns);
	Vertex_iterator vi;
	for(vi = tp.vertices_begin(); vi!=tp.vertices_end(); ++vi){
		if ((has_textures[vi]==1) && (this_type[vi])){
			load_vertex(vi, M);
		}
	}
	load_seam(tp, M);
}

void Pinned_matrix_loader::set_tags(TexturedPolyhedron& tp){
	Vertex_iterator vi;
	for(vi = tp.vertices_begin(); vi!=tp.vertices_end(); ++vi){
		(vi->u()[0] ==-1) ? this_type[vi] = false : this_type[vi] = true;
		has_textures[vi] = 1;
	}
	typename Halfedges::iterator hi, hinext;
	hinext = tp.seam->begin();
	for(hi = tp.seam->begin(); hinext!= tp.seam->end(); ++hi){
		hinext = hi;
		++hinext;
		++hinext;
		if (count_seam_neighbours((*hi)->vertex())==3)
			has_textures[(*hi)->vertex()] = 3;
		else
			has_textures[(*hi)->vertex()] = 2;
	}
}

void Pinned_matrix_loader::load_U(TexturedPolyhedron& tp, SparseMatrix<double>& U){
	set_tags(tp);
	int rowSize = count_this_type();
	U = SparseMatrix<double>(2 * rowSize, 1);
	Vertex_iterator vi;
	int row = 0;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		if (has_textures[vi]==1 && this_type[vi]) {
			U.insert(row, 0) = vi->u()[0];
			U.insert(row + rowSize, 0) = vi->v()[0];
			++row;
		}
	}
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		if (has_textures[vi]==2 && this_type[vi]) {
			U.insert(row, 0) = vi->u()[0];
			U.insert(row + rowSize, 0) = vi->v()[0];
			++row;
			U.insert(row, 0) = vi->u()[1];
			U.insert(row + rowSize, 0) = vi->v()[1];
			++row;
		}
	}
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		if (has_textures[vi]==3 && this_type[vi]) {
			U.insert(row, 0) = vi->u()[0];
			U.insert(row + rowSize, 0) = vi->v()[0];
			++row;
			U.insert(row, 0) = vi->u()[1];
			U.insert(row + rowSize, 0) = vi->v()[1];
			++row;
			U.insert(row, 0) = vi->u()[2];
			U.insert(row + rowSize, 0) = vi->v()[2];
			++row;
		}
	}
}

void Pinned_matrix_loader::load_vertex(Vertex_handle& v, Eigen::SparseMatrix<double>& M){
	if (has_textures[v]==1 && this_type[v]){
		int sizeColumns = count_this_type();
        HV_circulator h = v->vertex_begin();
        do {
        	Facet_handle f = h->facet();
        	//cout << f->id() << endl;
        	double f_dt = sqrt(2 * mc.calc_area(f));
        	double W[2];
        	mc.calc_W(f, v,  W);
        	M.insert (row[f], column[v][0]) = W[0] / f_dt;
        	M.insert (row[f] + row.size(), column[v][0]) = W[1] / f_dt;
        	M.insert(row[f], column[v][0] + sizeColumns) = -W[1] / f_dt;
        	M.insert(row[f] + row.size(), column[v][0] + sizeColumns) = W[0] / f_dt;
        } while ( ++h != v->vertex_begin());
	}
}

