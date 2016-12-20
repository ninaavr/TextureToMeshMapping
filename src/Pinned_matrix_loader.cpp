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

void Pinned_matrix_loader::load_M(TexturedPolyhedron& tp, Vertices& pinnedVertices, Eigen::SparseMatrix<double>& M){
	//if(pinnedVertices.size()<2){
	//	cout << "pinned Vertices must be at least 2!!" << endl;
	//	exit(-1);
	//}
	set_tags(tp, pinnedVertices);
	set_columns(tp);
	set_rows(tp);
	int sizeColumns = count_this_type() + count_this_seam();
	M = SparseMatrix<double>(2 * tp.size_of_facets(), sizeColumns);
	typename Vertices::iterator it;
	for( it = pinnedVertices.begin(); it != pinnedVertices.end(); ++it)
		load_vertex((*it), M);
	load_seam(tp, M);
}

void Pinned_matrix_loader::set_tags(TexturedPolyhedron& tp, Vertices& pinned){
	Vertex_iterator vi;
	for(vi = tp.vertices_begin(); vi!=tp.vertices_end(); ++vi){
		this_type[vi] = false;
		seam[vi] = false;
	}
	typename Vertices::iterator it;
	for(it=pinned.begin(); it != pinned.end(); ++it)
		this_type[*it] = true;
	typename Halfedges::iterator hi, hinext;
	hinext = tp.seam->begin();
	for(hi = tp.seam->begin(); hinext!= tp.seam->end(); ++hi){
		hinext = hi;
		++hinext;
		++hinext;
		seam[(*hi)->vertex()] = true;
	}
}

void Pinned_matrix_loader::load_U(Vertices& pinned, SparseMatrix<double>& U){
	U = SparseMatrix<double>(2 * pinned.size(), 1);
	typename Vertices::iterator it;
	int row = 0;
	for( it = pinned.begin(); it != pinned.end(); ++it){
		U.insert (row, 0) = (*it)->u();
		U.insert (row + pinned.size(), 0) = (*it)->v();
		++row;
	}
}

void Pinned_matrix_loader::load_vertex(Vertex_handle& v, Eigen::SparseMatrix<double>& M){
	if (!seam[v]){
        HV_circulator h = v->vertex_begin();
        do {
        	Facet_handle f = h->facet();
        	//cout << f->id() << endl;
        	double f_dt = 2 * mc.calc_area(f);
        	double W[2];
        	mc.calc_W(f, v,  W);
        	M.insert (row[f], column[v].first) = W[0] / f_dt;
        	M.insert (row[f] + row.size(), column[v].first) = W[1] / f_dt;
        } while ( ++h != v->vertex_begin());
	}
}

