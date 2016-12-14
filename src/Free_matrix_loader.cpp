/*
 * FreeMattrixLoader.cpp
 *
 *  Created on: 2 Dec 2016
 *      Author: osboxes
 */

#include "Free_matrix_loader.h"

using namespace Eigen;
Free_matrix_loader::Free_matrix_loader() {
	// TODO Auto-generated constructor stub

}

Free_matrix_loader::~Free_matrix_loader() {
	// TODO Auto-generated destructor stub
}

void Free_matrix_loader::load_M(TexturedPolyhedron& tp, Vertices& pinnedVertices, Eigen::SparseMatrix<double>& M) {
	//stores the free vertices in a list
	Vertices freeVertices;
	get_free_vertices(tp, pinnedVertices, freeVertices);
	set_tags(tp, pinnedVertices);
	//number of facets x number of vertices, border vertices are added twice for each border
	int sizeFreeSeamVertices = count_seam_vertices(freeVertices);
	//cout << freeVertices.size() << endl;
	//cout << sizeFreeSeamVertices << endl;
	//cout << tp.size_of_facets() << endl;
	M = SparseMatrix<double>(2 * tp.size_of_facets(), freeVertices.size() + sizeFreeSeamVertices);

	//set to which row corresponds each vertex
	setColumns_M(freeVertices);

	//allocate arrays to store temporary values
	double W[3];  double W2[3];   //K::Point_2 p[3];

	int f_row = 0;
	//calculates values for M and loads M if vertices are not at border
	for (Facet_iterator f = tp.facets_begin(); f != tp.facets_end(); ++f) {
		row[f] = f_row;
		//mc.project_triangle(f, p);
		//double dt = 2*Facet_area<TexturedPolyhedron::>(f);
		double f_dt = 2 * mc.calc_area(f);

		K::Point_2 p[3];
		mc.project_triangle(f, p);
		//mc.calc_W(p, true, W);
		//mc.calc_W(p, false, W2);
		int i = 0;
		HF_circulator h = f->facet_begin();
		do {
			Vertex_handle v = h->vertex();
			//cout << "check if free & not seam   "<< h->vertex()->id() << endl;
			if (!(seam[v]) && !(pinned[v])) {
				//M.insert(f_row, column[h->vertex()].first) = W[i] /std::sqrt(f_dt);
				//M.insert(f_row + tp.size_of_facets(), column[h->vertex()].first) = W2[i] / std::sqrt(f_dt);
				M.insert(f_row, column[h->vertex()].first) = 1;
				M.insert(f_row + tp.size_of_facets(), column[h->vertex()].first) = 1;
			}
			++i;
		} while (++h != f->facet_begin());
		++f_row;
	}
	load_seam_vertices_M(tp, M);
	cout << M << endl;
}


void Free_matrix_loader::get_free_vertices(TexturedPolyhedron& tp, Vertices pinned, Vertices& free) {
	TexturedPolyhedron::Vertex_iterator hi;
	typename Vertices::iterator it, itnext;
	for (hi = tp.vertices_begin(); hi != tp.vertices_end(); ++hi) {
		if (!pinned.empty()) {
			for (it = pinned.begin(); it != pinned.end(); ++it) {
				itnext = it;
				++ itnext;
				//if we found vi in the pinned list we omit it and go to the next vi
				//we erase locally the pinned vertex from the list of pinned vertices
				if ((hi == *it)){
					//cout << "pinned found " << endl;
					pinned.erase(it);
					break;
				}
				//if vi is not in the whole pinned list it is set in freeVertices
				else if (itnext == pinned.end()){
					free.push_back(hi);
				}
			}
		} else { //add vertices directly in the list when no pinned vertices are left
			free.push_back(hi);
		}
	}
}
