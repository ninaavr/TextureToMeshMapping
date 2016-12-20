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

void Free_matrix_loader::load_M(TexturedPolyhedron& tp, Vertices& pinnedVertices, Eigen::SparseMatrix<double>& M) {
	set_tags(tp, pinnedVertices);
	//number of facets x number of vertices, seam vertices are added twice for each border
	int sizeColumns = count_this_type() + count_this_seam();
	M = SparseMatrix<double>(2 * tp.size_of_facets(), sizeColumns);
	//set to which row corresponds each vertex
	set_columns(tp);
	set_rows(tp);
	//allocate arrays to store temporary values
	double W[6];
	//calculates values for M and loads M if vertices are not at border
	for (Facet_iterator f = tp.facets_begin(); f != tp.facets_end(); ++f) {
		double f_dt = 2 * mc.calc_area(f);
		mc.calc_W(f, W);
		int i = 0;
		HF_circulator h = f->facet_begin();
		do {
			Vertex_handle v = h->vertex();
			//cout << "check if free & not seam   "<< h->vertex()->id() << endl;
			if (!(seam[v]) && (this_type[v])) {
				M.insert(row[f], column[h->vertex()].first) = W[i] /f_dt;
				M.insert(row[f] + tp.size_of_facets(), column[h->vertex()].first) = W[i+3] / f_dt;
			}
			++i;
		} while (++h != f->facet_begin());
	}
	load_seam(tp, M);
	//cout << M << endl;
}

void Free_matrix_loader::set_tags(TexturedPolyhedron& tp, Vertices& pinned){
	Vertex_iterator vi;
	for(vi = tp.vertices_begin(); vi!=tp.vertices_end(); ++vi){
		this_type[vi] = true;
		seam[vi] = false;
	}
	typename Vertices::iterator it;
	for(it=pinned.begin(); it != pinned.end(); ++it)
		this_type[*it] = false;
	typename Halfedges::iterator hi, hinext;
	hinext = tp.seam->begin();
	for(hi = tp.seam->begin(); hinext!= tp.seam->end(); ++hi){
		hinext = hi;
		++hinext;
		++hinext;
		seam[(*hi)->vertex()] = true;
	}
}

