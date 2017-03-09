/*
 * MatrixLoader.cpp
 *
 *  Created on: 28 Nov 2016
 *      Author: osboxes
 */

#include "Matrix_loader.h"
using namespace Eigen;

Matrix_loader::Matrix_loader() {
}

Matrix_loader::~Matrix_loader() {
}

void Matrix_loader::set_rows(TexturedPolyhedron& tp) {
	Facet_iterator fi;
	int index = 0;
	for(fi = tp.facets_begin(); fi != tp.facets_end(); ++fi){
		row[fi] = index;
		++index;
	}
}

void Matrix_loader::set_columns(TexturedPolyhedron& tp) {
	int index = 0;
	int index2 = 0;
	int sizeInnerVertices = count_this_type() - count_this_seam();
	TexturedPolyhedron::Vertex_iterator vi;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		if(this_type[vi]){
			if (seam[vi]) {
				column[vi].first = index2 + sizeInnerVertices;
				//cout << (vi)->id() << "   at   " << index2 + sizeInnerVertices	<< endl;
				column[vi].second = index2 + sizeInnerVertices + 1;
				index2 += 2;
			} else {
				//cout << (vi)->id() << "   at   " << index << endl;
				column[vi].first = index;
				column[vi].second = -1;
				++index;
			}
		}
	}
}

void Matrix_loader::load_seam(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M) {
	//prev and next are the 2 edges on the border surrounding v
	typename std::list<Halfedge_handle>::iterator prev, next;
	prev = tp.seam->begin();
	next = prev;
	++next;
	//do for all vertices on seam
	while (next != tp.seam->end()) {
		Vertex_handle v = (*prev)->vertex();
		Halfedge_iterator hi = (*prev);
		//skip vertices not from this type
		if (this_type[v]){
			//all facets with v on first side of the border
			for (; hi != (*next)->opposite(); hi = hi->next_on_vertex()){
				load_seam_face(v, hi->face(), true, M);
				//hi takes halfedges pointing to v
			}
			//all facets with v on second side of the border
			for (; hi != (*prev); hi = hi->next_on_vertex()){
				load_seam_face(v, hi->face(), false, M);
			}
		}
		++prev;	++next;
	}
}


void Matrix_loader::load_seam_face(Vertex_handle v, Facet_handle f, const bool left, Eigen::SparseMatrix<double>& M) {
	int col;
	(left) ? col = column[v].first : col = column[v].second;
	double area = sqrt(2 * mc.calc_area(f));;
	double W[2];
	mc.calc_W(f, v, W);
	int sizeColumns = count_this_type();
	//calc u and v
	M.coeffRef(row[f], col) = W[0]/ area;
	M.coeffRef(row[f] + row.size(), col) = W[1] / area;
	M.coeffRef(row[f], col + sizeColumns) = -W[1] / area;
	M.coeffRef(row[f] + row.size(), col + sizeColumns) = W[0] / area;
}


int Matrix_loader::count_this_seam(){
	typename Tag::iterator it;
	int size = 0;
	for (it = this_type.begin(); it != this_type.end(); ++it){
		if(it->second && seam[it->first])
			size+=2;
	}
	return size;
}

int Matrix_loader::count_this_type(){
	typename Tag::iterator it;
	int size = 0;
	for (it = this_type.begin(); it != this_type.end(); ++it){
		if (it->second)
			++size;
		if(it->second && seam[it->first])
			++size;
	}
	return size;
}
