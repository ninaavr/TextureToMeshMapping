/*
 * MatrixLoader.cpp
 *
 *  Created on: 28 Nov 2016
 *      Author: osboxes
 */

#include "MatrixLoader.h"
using namespace Eigen;

MatrixLoader::MatrixLoader() {
	// TODO Auto-generated constructor stub

}

MatrixLoader::~MatrixLoader() {
	// TODO Auto-generated destructor stub
}

void MatrixLoader::load_M(TexturedPolyhedron& tp, Eigen::SparseMatrix<double>& M) {
	M = Eigen::SparseMatrix<double>(2 * tp.size_of_facets(),
			tp.size_of_vertices());
	//set to which row corresponds each vertex
	Column column;
	Column_border column_border;
	Row row;
	setColumns_M(tp, column, column_border);

	double W[3]; double W2[3];
	K::Point_2 p[3];
	//iterators
	int f_row = 0;
	HF_circulator h;

	//calculates values for M and loads M if vertices are not at border
	for (Facet_iterator f = tp.facets_begin(); f != tp.facets_end(); ++f) {
		h = f->facet_begin();
		row[f] = f_row;
		project_triangle(f, p);
		calc_W(p, true, W);
		calc_W(p, false, W2);
		int i = 0;
		do {
			if (!h->vertex()->is_border()) {
				M.insert(f_row, column[h->vertex()]) = W[i] / std::sqrt(calc_dt(p));
				M.insert(f_row + tp.size_of_facets(), column[h->vertex()]) = W2[i] / std::sqrt(calc_dt(p));
			}
			++i;
		} while (++h != f->facet_begin());
		++f_row;
	}
	Halfedge_iterator hf;
	//tp.border.push_back(tp.halfedges_begin());
	//hf = tp.halfedges_begin();
	//tp.border->push_back(tp.halfedges_begin());
	//std::list<Halfedge_handle> b;
	//b = *tp.border;
	//b.push_back(tp.halfedges_begin());
	//for (hf = tp.border->front(); hf != b.back(); ++hf) {
		//cout << "test border list" << endl;
	//}

	//calculates values for M and loads M at border


}

double MatrixLoader::calc_W(Facet_iterator f, Vertex_handle& v,
		bool firstText) {
	HF_circulator h = f->facet_begin();
	if (h->vertex() != v) {
		++h;
	}
	HF_circulator hnext = h;
	++hnext;
	double W;
	(firstText) ?
			W = hnext->vertex()->point().x() - h->vertex()->point().x() :
			hnext->vertex()->point().y() - h->vertex()->point().y();
	double height = hnext->vertex()->point().z() - h->vertex()->point().z();
	return sqrt(W * W + height * height);
}

void MatrixLoader::calc_W(K::Point_2* p, bool firstText, double * W) {
	for (int i = 0; i < 3; ++i) {
		(firstText) ?
				W[i] = p[(i + 2) % 3].x() - p[(i + 1) % 3].x() :
				W[i] = p[(i + 2) % 3].y() - p[(i + 1) % 3].y();
	}
}

void MatrixLoader::project_triangle(Facet_iterator f, K::Point_2* p) {
	HF_circulator h = f->facet_begin();
	//calculate centre of coordinate system
	double meanX, meanY, meanZ = 0;
	double x, y, height;
	do {
		meanX += h->vertex()->point().x() / 3;
		meanY += h->vertex()->point().y() / 3;
		meanZ += h->vertex()->point().z() / 3;
	} while (++h != f->facet_begin());

	for (int i = 0; i < 3; ++i) {
		//perform shift according to new coordinate system
		x = h->vertex()->point().x() - meanX;
		y = h->vertex()->point().y() - meanY;
		height = h->vertex()->point().z() - meanZ;

		//calculate distances in 2D
		x = x * x + height * height;
		y = y * y + height * height;

		p[i] = K::Point_2(x, y);
		++h;
	}
}

void MatrixLoader::setColumns_M(TexturedPolyhedron& tp, Column& column,
		Column_border& column_border) {
	int index, index2, index3 = 0;
	int sizeNormalVertices = tp.size_of_vertices() - tp.sizePinnedVertices
			- 2 * tp.sizeBorderVertices;
	for (Vertex_iterator vi = tp.vertices_begin(); vi != tp.vertices_end();
			++vi) {
		if (vi->is_pinned()) {
			column[vi] = index + sizeNormalVertices + 2 * tp.sizeBorderVertices;
			++index;
		} else if (vi->is_border()) {
			column_border[vi].first = index2 + sizeNormalVertices;
			column_border[vi].second = index2 + sizeNormalVertices + 1;
			index2 += 2;
		} else {
			column[vi] = index3;
			++index3;
		}
	}
}

double MatrixLoader::calc_dt(K::Point_2* p) {
	// (x1*y2 −y1*x2) + (x2*y3 −y2*x3) + (x3*y1 −y3*x1)
	double result = p[0].x() * p[1].y() - p[0].y() * p[1].x();
	result += p[1].x() * p[2].y() - p[1].y() * p[2].x();
	result += p[2].x() * p[0].y() - p[2].y() * p[0].x();
	return result;
}

void MatrixLoader::calculate_triangle_gradient(Facet_iterator f, double* W,
		double& dt) {
	// h = vertex 2; hnext = vertex 3
	HF_circulator h = f->facet_begin();
	++h;
	HF_circulator hnext = h;
	++hnext;
	double height;
	dt = 0;
	for (int i = 0; i < 3; ++i) {
		//x3 - x2; x1 - x3; x2 - x1;
		W[i] = hnext->vertex()->point().x() - h->vertex()->point().x();
		//y3 - y2; y1 - y3; y2 - y1;
		W[i + 3] = hnext->vertex()->point().y() - h->vertex()->point().y();

		//calculate real 3D distance
		height = hnext->vertex()->point().z() - h->vertex()->point().z();
		W[i] = W[i] * W[i] + height * height;
		W[i] = std::sqrt(W[i]);
		W[i + 3] = W[i + 3] * W[i + 3] + height * height;
		W[i + 3] = std::sqrt(W[i + 3]);

		//y3*x2 - x3*y2  +  y1*x3 - x1*y3  +  y2*x1 - x2*y1
		dt += hnext->vertex()->point().y() * h->vertex()->point().x();
		dt -= hnext->vertex()->point().x() * h->vertex()->point().y();
		++h;
		++hnext;
	}
}
