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
	int index3 = 0;
	int sizeInnerVertices = count_this_type() - count_this_seam() - count_this_branch();
	//this_seam has 2 columns per vertex
	int sizeNonBranches = count_this_type() - count_this_branch();
	TexturedPolyhedron::Vertex_iterator vi;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		column[vi] = new int[3];
		if(this_type[vi]){
			if (has_textures[vi]==3) {
				column[vi][0] = index3 + sizeNonBranches;
				column[vi][1] = index3 + sizeNonBranches +1;
				column[vi][2] = index3 + sizeNonBranches +2;
				index3 += 3;
			}else if (has_textures[vi]==2) {
				//cout << (vi)->id() << "   at   " << index2 + sizeInnerVertices	<< endl;
				column[vi][0] = index2 + sizeInnerVertices;
				column[vi][1] = index2 + sizeInnerVertices + 1;
				column[vi][2] = -1;
				index2 += 2;
			} else if (has_textures[vi]==1){
				//cout << (vi)->id() << "   at   " << index << endl;
				column[vi][0] = index;
				column[vi][1] = -1;
				column[vi][2] = -1;
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
				if (has_textures[(*prev)->vertex()]==2) {
					if(are_sharing_vertex(*prev, *next)){
						load_seam_between(*prev, *next, 0, M);
						load_seam_between((*next)->opposite(), (*prev)->opposite(), 1, M);
					}
				} else {
					typename std::list<Halfedge_handle>::iterator branch =  next;
					++branch;
					while (!are_sharing_vertex(*prev, *branch))
						++branch;
					if(halfedge_is_between(*branch, *prev, *next)){
						load_seam_between(*prev, *branch, 0, M);
						load_seam_between((*branch)->opposite(), *next, 1, M);
						load_seam_between((*next)->opposite(), (*prev)->opposite(), 2, M);
					} else{
						load_seam_between(*prev, *next, 0, M);
						load_seam_between((*next)->opposite(), *branch, 1, M);
						load_seam_between((*branch)->opposite(), (*prev)->opposite(), 2, M);
					}
			}
			prev = next;
			++next;
		}
	//prev and next are the 2 edges on the border surrounding v
	/*typename std::list<Halfedge_handle>::iterator prev, next;
	prev = tp.seam->begin();
	next = prev;
	++next;
	//do for all vertices on seam
	while (next != tp.seam->end()) {
		Vertex_handle v = (*prev)->vertex();
		Halfedge_iterator hi = (*prev);
		//skip vertices not from this type
		if (this_type[v]){
			int sizeColumns = count_this_type();
			if(has_textures[v]<3){ //normal seam vertices
				//all facets with v on first side of the border
				load_seam_between(*prev, *next, 0, M);
				//all facets with v on second side of the border
				load_seam_between((*next)->opposite(), (*prev)->opposite(), 1, M);
			}
			if(has_textures[v]==3){

			}
		}
		++prev;	++next;
	}*/
}



void Matrix_loader::load_seam_between(const Halfedge_handle& prev,const Halfedge_handle& next, const int side, Eigen::SparseMatrix<double>& M) {
	Halfedge_iterator hi = prev;
	Vertex_handle v = prev->vertex();
	int sizeColumns = count_this_type();
	if (this_type[v]) {
		for (; hi != next->opposite(); hi = hi->next_on_vertex())
			load_seam_face(v, hi->face(), side, sizeColumns, M);
	}
}

bool Matrix_loader::halfedge_is_between(const Halfedge_handle& this_h, const Halfedge_handle& prev, const Halfedge_handle& next){
	bool is_between = false;
	Halfedge_iterator hi;
	for (hi = prev; hi != next->opposite(); hi = hi->next_on_vertex()){
		if(hi == this_h->opposite())
			is_between = true;
	}
	return is_between;
}

void Matrix_loader::load_seam_face(Vertex_handle v, Facet_handle f, const int side, int sizeColumns, Eigen::SparseMatrix<double>& M) {
	int col;
	col = column[v][side];
	//(side==0) ? col = column[v][0] : col = column[v][1];
	//(has_textures[v]==3)? f->is_branch_side()= side : f->is_seam_side() = side;

	//set side for facet for corresponding vertex
	HF_circulator h = f->facet_begin();
	int i = 0;
	while(h->vertex()!=v){
		++h;
		++i;
	}
	f->is_side()[i] = side;
	double area = sqrt(2 * mc.calc_area(f));
	double W[2];
	mc.calc_W(f, v, W);
	//calc u and v
	M.coeffRef(row[f], col) = W[0]/ area;
	M.coeffRef(row[f] + row.size(), col) = W[1] / area;
	M.coeffRef(row[f], col + sizeColumns) = -W[1] / area;
	M.coeffRef(row[f] + row.size(), col + sizeColumns) = W[0] / area;
}

bool Matrix_loader::are_sharing_vertex(Halfedge_handle& h1, Halfedge_handle& h2) {
	Halfedge_iterator hi = h1->next_on_vertex();
	bool are_sharing = false;
	while (hi != h1) {
		if (hi == h2->opposite())
			are_sharing = true;
		hi = hi->next_on_vertex();
	}
	return are_sharing;
}

int Matrix_loader::count_seam_neighbours(const TexturedPolyhedron::Vertex_handle& v){
	int size = 0;
	TexturedPolyhedron::Halfedge_around_vertex_circulator h;
	h = v->vertex_begin();
	do {
		if (h->is_seam()||h->opposite()->is_seam())
			size++;
	} while (++h != v->vertex_begin());
	return size;
}

int Matrix_loader::count_this_branch(){
	typename Tag::iterator it;
	int size = 0;
	for (it = this_type.begin(); it != this_type.end(); ++it){
		if(it->second && has_textures[it->first]==3)
			size+=3;
	}
	return size;
}

int Matrix_loader::count_this_seam(){
	typename Tag::iterator it;
	int size = 0;
	for (it = this_type.begin(); it != this_type.end(); ++it){
		if(it->second && has_textures[it->first]==2)
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
		if(it->second && has_textures[it->first]==2)
			++size;
		if(it->second && has_textures[it->first]==3)
			size+=2;
	}
	return size;
}
