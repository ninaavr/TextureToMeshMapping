/*
 * FreeMattrixLoader.cpp
 *
 *  Created on: 2 Dec 2016
 *      Author: osboxes
 */

#include "Free_matrix_loader.h"

using namespace Eigen;
Free_matrix_loader::Free_matrix_loader() {
}

Free_matrix_loader::~Free_matrix_loader() {
}

void Free_matrix_loader::load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M) {
	set_tags(tp);
	//number of facets x number of vertices, seam vertices are added twice for each border
	int sizeColumns = count_this_type();
	M = SparseMatrix<double>(2 * tp.size_of_facets(), 2 * sizeColumns);
	//set to which row corresponds each vertex
	set_columns(tp);
	set_rows(tp);
	//allocate arrays to store temporary values
	double W[6];
	//calculates values for M and loads M if vertices are not at border
	for (Facet_iterator f = tp.facets_begin(); f != tp.facets_end(); ++f) {
		double f_dt = sqrt(2 * mc.calc_area(f));
		mc.calc_W(f, W);
		int i = 0;
		HF_circulator h = f->facet_begin();
		do {
			Vertex_handle v = h->vertex();
			//cout << "check if free & not seam   "<< h->vertex()->id() << endl;
			if ((has_textures[v] == 1) && (this_type[v])) {
				M.insert(row[f], column[h->vertex()][0]) = W[i] / f_dt;
				M.insert(row[f] + tp.size_of_facets(), column[h->vertex()][0]) = W[i + 3] / f_dt;
				M.insert(row[f], column[h->vertex()][0] + sizeColumns) = -W[i + 3] / f_dt;
				M.insert(row[f] + tp.size_of_facets(), column[h->vertex()][0] + sizeColumns) = W[i] / f_dt;
			}
			++i;
		} while (++h != f->facet_begin());
	}
	load_seam(tp, M);
	//cout << M << endl;
}

void Free_matrix_loader::set_tags(TexturedPolyhedron& tp) {
	Vertex_iterator vi;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		if (vi->u()[0] == -1)
			this_type[vi] = true;
		else
			this_type[vi] = false;
		has_textures[vi] = 1;
	}
	typename Halfedges::iterator hi, hinext;
	hinext = tp.seam->begin();
	for (hi = tp.seam->begin(); hinext != tp.seam->end(); ++hi) {
		hinext = hi;
		++hinext;
		++hinext;
		if (count_seam_neighbours((*hi)->vertex()) == 3)
			has_textures[(*hi)->vertex()] = 3;
		else
			has_textures[(*hi)->vertex()] = 2;
	}
}

void Free_matrix_loader::store_result(Eigen::VectorXd& textures,
		TexturedPolyhedron& tp) {
	int num_vert = count_this_type();
	TexturedPolyhedron::Vertex_iterator vi;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		if (this_type[vi]){ //no change for fixed vertices
			vi->u()[0] = textures[column[vi][0]];
			vi->v()[0] = textures[column[vi][0] + num_vert];
				//cout << "u   " << vi->u()<< "   v   " << vi->v() << endl;
			if (has_textures[vi] > 1 ) { //seam vertices
				vi->u()[1] = textures[column[vi][1]];
				vi->v()[1] = textures[column[vi][1] + num_vert];
				//cout << "u   " << vi->u()[1]<< "   v   " << vi->v()[1] << endl;
			}
			if (has_textures[vi]==3) { //branch seam vertices
				vi->u()[2] = textures[column[vi][2]];
				vi->v()[2] = textures[column[vi][2] + num_vert];
				//cout << "u   " << vi->u()[2]<< "   v   " << vi->v()[2] << endl;
			}
		}
	}
	tp.texturesExist = true;
}
