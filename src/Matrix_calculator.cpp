/*
 * Matrixcalculator.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: osboxes
 */

#include "Matrix_calculator.h"

Matrix_calculator::Matrix_calculator() {
	// TODO Auto-generated constructor stub

}

Matrix_calculator::~Matrix_calculator() {
	// TODO Auto-generated destructor stub
}


double Matrix_calculator::calc_area(TexturedPolyhedron::Face_handle& f) {
	return K::Compute_area_3()(f->halfedge()->vertex()->point(),
			f->halfedge()->next()->vertex()->point(),
			f->halfedge()->opposite()->vertex()->point());
}

void Matrix_calculator::calc_W(Facet_handle& f, Vertex_handle& v, double* W) {
	//find the position of the vertex in f
	HF_circulator h = f->facet_begin();
	int i = 0;
	while (h->vertex() != v){
		++h; ++i;
	}
	K::Point_2 p[3];
	project_triangle(f, p);
	W[0] = p[(i + 2) % 3].x() - p[(i + 1) % 3].x();
	W[1] =  p[(i + 2) % 3].y() - p[(i + 1) % 3].y();
}

void Matrix_calculator::calc_W(Facet_handle& f, double * W) {
	K::Point_2 p[3];
	project_triangle(f, p);
	for (int i = 0; i < 3; ++i) {
		W[i] = p[(i + 2) % 3].x() - p[(i + 1) % 3].x();
		W[i+3] = p[(i + 2) % 3].y() - p[(i + 1) % 3].y();
	}
}

void Matrix_calculator::project_triangle(Facet_handle f, K::Point_2* p) {
	//cout << f->id() << endl;
	//shift of the coordinate system to one of the vertices
	HF_circulator h = f->facet_begin();
	K::Vector_3 v1 = h ->vertex()->point() - CGAL::ORIGIN;
	CGAL::Aff_transformation_3<K> translate (CGAL::TRANSLATION, -v1);
	//rotation of the coordinate system to z axis - normal and x axis - a side of the triangle
	K::Vector_3 Z = h ->facet()->normal();
	K::Vector_3 X = translate (h->next()->vertex()->point()) - CGAL::ORIGIN;
	normalise(X);
	K::Vector_3 Y = CGAL::cross_product(Z, X);
	CGAL::Aff_transformation_3<K> rotate (K::RT(X.x()),K::RT(X.y()),K::RT(X.z()),
									  K::RT(Y.x()),K::RT(Y.y()),K::RT(Y.z()),
									  K::RT(Z.x()),K::RT(Z.y()),K::RT(Z.z()));
	//shift of the  coordinate system to the centre of the triangle
	K::Vector_3 centre;
	calc_centre(f, centre);
	CGAL::Aff_transformation_3<K> translate2 (CGAL::TRANSLATION, -centre);

	//perform transformations
	K::Point_3 p_dim3;
	int i = 0;
	do{
		p_dim3 = translate(h->vertex()->point());
		p_dim3 = rotate (p_dim3);
		p_dim3 = translate2(p_dim3);
		p[i] = K::Point_2(p_dim3.x(), p_dim3.y());
		++i;
	}while (++h != f->facet_begin());
}

void Matrix_calculator::normalise(K::Vector_3& v){
	double sq_sum = v*v;
	if(sq_sum != 0)
		v = v/sqrt(sq_sum);
}

void Matrix_calculator::calc_centre(Facet_handle& f, K::Vector_3& centre){
	HF_circulator h = f->facet_begin();
	double mean[3];
	mean[0] = 0; mean[1] = 0; mean[2] = 0;
	do{
		mean[0] += h->vertex()->point().x()/3;
		mean[1] += h->vertex()->point().y()/3;
		mean[2] += h->vertex()->point().z()/3;
	}while (++h != f->facet_begin());
	centre = K::Vector_3(mean[0], mean[1], mean[2]);
}
