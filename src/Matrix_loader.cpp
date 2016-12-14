/*
 * MatrixLoader.cpp
 *
 *  Created on: 28 Nov 2016
 *      Author: osboxes
 */

#include "Matrix_loader.h"
using namespace Eigen;

Matrix_loader::Matrix_loader() {
	// TODO Auto-generated constructor stub

}

Matrix_loader::~Matrix_loader() {
	// TODO Auto-generated destructor stub
}

int Matrix_loader::count_seam_vertices(Vertices& vertices) {
	int sizeBorderVertices = 0;
	typename Vertices::iterator it;
	for (it = vertices.begin(); it != vertices.end(); ++it) {
		if (seam[*it])
			++sizeBorderVertices;
	}
	return sizeBorderVertices;
}

void Matrix_loader::setColumns_M(Vertices& vertices) {
	int index = 0;
	int index2 = 0;
	int sizeInnerVertices = vertices.size() - count_seam_vertices(vertices);
	typename Vertices::iterator it;
	for (it = vertices.begin(); it != vertices.end(); ++it) {
		if (seam[*it]) {
			column[*it].first = index2 + sizeInnerVertices;
			cout << (*it)->id() << "   at   " << index2 + sizeInnerVertices	<< endl;
			column[*it].second = index2 + sizeInnerVertices + 1;
			index2 += 2;
		} else {
			cout << (*it)->id() << "   at   " << index << endl;
			column[*it].first = index;
			++index;
		}
	}
}

void Matrix_loader::set_tags(TexturedPolyhedron& tp, Vertices& pinnedVertices) {
	Vertex_iterator vi;
	for (vi = tp.vertices_begin(); vi != tp.vertices_end(); ++vi) {
		seam[vi] = false;
		//(is_seam(vi))? seam[vi] = true : seam[vi] =false;
		(is_pinned(vi, pinnedVertices)) ? pinned[vi] = true : pinned[vi] =
													false;
	}
	typename std::list<Halfedge_handle>::iterator it, it_next;
	it = tp.seam->begin();
	it_next = it;
	++it_next;
	while (it_next != tp.seam->end()) {
		seam[(*it)->vertex()] = true;
		++it;
		++it_next;
	}
}

bool Matrix_loader::is_pinned(const Vertex_handle& v, Vertices& pinned) {
	typename Vertices::iterator it = pinned.begin();
	bool is_pinned = false;
	while (it != pinned.end() && !is_pinned) {
		if (*it == v)
			is_pinned = true;
		++it;
	}
	return is_pinned;
}

bool Matrix_loader::is_seam(const Vertex_handle& v) {
	HV_circulator hv = v->vertex_begin();
	bool is_seam = false;
	do {
		if (hv->is_seam()) {
			is_seam = true;
		}
	} while (++hv != v->vertex_begin() && !is_seam);
	return is_seam;
}

void Matrix_loader::load_list_in_M(std::list<Halfedge_handle>& list,
		Eigen::SparseMatrix<double>& M) {
	K::Point_2 facedim2[3];
	Vertex_handle v1, v2;
	Facet_handle face;
	double sqrt_f_dt;
	typename std::list<Halfedge_handle>::iterator it;
	for (it = list.begin(); it != list.end(); ++it) {
		v1 = (*it)->opposite()->vertex();
		v2 = (*it)->vertex();
		//first face
		face = (*it)->facet();
		mc.project_triangle(face, facedim2);
		sqrt_f_dt = sqrt(mc.calc_dt(facedim2));
		//first vertex in first face
		M.insert(row[face], column[v1].first) = mc.calc_W(face, v1, true)
				/ sqrt_f_dt;
		M.insert(row[face] + row.size(), column[v1].first) = mc.calc_W(face, v1,
				false) / sqrt_f_dt;
		//second vertex in first face
		M.insert(row[face], column[v2].first) = mc.calc_W(face, v2, true)
				/ sqrt_f_dt;
		M.insert(row[face] + row.size(), column[v2].first) = mc.calc_W(face, v2,
				false) / sqrt_f_dt;
		//second face
		face = (*it)->opposite()->facet();
		mc.project_triangle(face, facedim2);
		sqrt_f_dt = sqrt(mc.calc_dt(facedim2));
		//first vertex in second face
		M.insert(row[face], column[v1].second) = mc.calc_W(face, v1, true)
				/ sqrt_f_dt;
		M.insert(row[face] + row.size(), column[v1].second) = mc.calc_W(face,
				v1, false) / sqrt_f_dt;
		//second vertex in second face
		M.insert(row[face], column[v2].second) = mc.calc_W(face, v2, true)
				/ sqrt_f_dt;
		M.insert(row[face] + row.size(), column[v2].second) = mc.calc_W(face,
				v2, false) / sqrt_f_dt;
		cout << "test border list" << endl;
	}
}

void Matrix_loader::load_halfedge_in_M(Halfedge_handle h, Eigen::SparseMatrix<double>& M, const bool secondBorder) {
	K::Point_2 facedim2[3];
	Facet_handle face = h->facet();
	mc.project_triangle(face, facedim2);
	double sqrt_f_dt = sqrt(mc.calc_dt(facedim2));
	Vertex_handle v = h->vertex();
	int col;
	(secondBorder) ? col = column[v].second : col = column[v].first;
	if (!pinned[v]) {
		//first vertex in the face
		cout << "IDs, vertex:    " << v->id() << "    face:   " << face->id()
				<< endl;
		cout << row[face] << "    " << col << endl;
		//M.coeffRef (row[face], col) = mc.calc_W(face, v, true) / sqrt_f_dt;
		M.coeffRef(row[face], col) = 1;
		cout << row[face] + row.size() << "    " << col << endl;
		//M.coeffRef (row[face] + row.size(), col) = mc.calc_W(face, v, false) / sqrt_f_dt;
		M.coeffRef(row[face] + row.size(), col) = 1;
	}
	v = h->opposite()->vertex();
	(secondBorder) ? col = column[v].second : col = column[v].first;
	//second vertex in the face
	if (!pinned[v]) {
		cout << "IDs, vertex:" << v->id() << "    face:   " << face->id()
				<< endl;
		cout << row[face] << "    " << col << endl;
		//M.coeffRef (row[face], col) = mc.calc_W(face, v, true) / sqrt_f_dt;
		M.coeffRef(row[face], col) = 1;
		cout << row[face] + row.size() << "    " << col << endl;
		//M.coeffRef(row[face] + row.size(), col) = mc.calc_W(face, v, false) / sqrt_f_dt;
		M.coeffRef(row[face] + row.size(), col) = 1;
	}
}

void Matrix_loader::load_seam_vertices_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M) {
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
		if (!pinned[v]){
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


void Matrix_loader::load_seam_face(Vertex_handle v, Facet_handle f, const bool first, SparseMatrix<double>& M) {
	int col;
	(first) ? col = column[v].first : col = column[v].second;
	double area = mc.calc_area(f);
	//calc u
	M.coeffRef(row[f], col) = 1;//mc.calc_W(f, v, true)/ (2 * area);
	M.coeffRef(row[f] + row.size(), col) = 1;//mc.calc_W(f, v, false) / (2 * area);
	//calc v
	M.coeffRef(row[f], col) = 1;//mc.calc_W(f, v, true) / (2 * area);
	M.coeffRef(row[f] + row.size(), col) = 1;//mc.calc_W(f, v, false) / (2 * area);
}

