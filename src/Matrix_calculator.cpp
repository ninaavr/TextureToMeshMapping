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

double Matrix_calculator::calc_W(const Facet_iterator f, const Vertex_handle& v,
		const bool firstText) {
	HF_circulator h = f->facet_begin();
	while (h->vertex() != v)
		++h;
	double W;
	(firstText) ?
			W = h->next()->vertex()->point().x() - h->vertex()->point().x() :
			h->next()->vertex()->point().y() - h->vertex()->point().y();
	double height = h->next()->vertex()->point().z() - h->vertex()->point().z();
	return sqrt(W * W + height * height);
}

void Matrix_calculator::calc_W(K::Point_2* p, bool firstText, double * W) {
	for (int i = 0; i < 3; ++i) {
		(firstText) ?
				W[i] = p[(i + 2) % 3].x() - p[(i + 1) % 3].x() :
				W[i] = p[(i + 2) % 3].y() - p[(i + 1) % 3].y();
	}
}

void Matrix_calculator::project_triangle(Facet_iterator f, K::Point_2* p) {
	cout << f->id() << endl;
	HF_circulator h = f->facet_begin();
	K::Point_3 p_3d [3];
	p_3d [0] = h->vertex()->point();
	p_3d [1] = h->next()->vertex()->point();
	p_3d [2] = h->next()->next()->vertex()->point();
	double mean[3];
	mean[0] = 0; mean[1] = 0; mean[2] = 0;
	for (int i = 0; i < 3; ++i){
		mean[0] += p_3d[i].x() / 3;
		mean[1] += p_3d[i].y() / 3;
		mean[2] += p_3d[i].z() / 3;
	}
	K::Vector_3 centre = K::Vector_3(mean[0], mean[1], mean[2]);
	CGAL::Aff_transformation_3<K> t (CGAL::TRANSLATION, -centre);

	K::Vector_3 xz = K::Vector_3(h->facet()->normal().x(), 0, h->facet()->normal().z());
	normalise(xz);
	//if normal lies on the axis of y, xz is 0
	if (xz*xz == 0)
		xz = K::Vector_3(0, 0, 1);

	//cos alpha
	double cos = h->facet()->normal() * xz;
	//sin alpha
	K::Vector_3 orthVector = CGAL::cross_product(h->facet()->normal(), xz);
	double sin = sqrt(orthVector * orthVector);

	//get correct sign for sin
	if (orthVector.y()<0)
		sin = -sin;
	//if (h->facet()->normal().y()<0)
		//cos = -cos;


	//cout << "face id  "<< h->facet()->id() << endl;

	CGAL::Aff_transformation_3<K> rot (K::RT(1),K::RT(0),K::RT(0),
									   K::RT(0),K::RT(cos),K::RT(-sin),
									   K::RT(0),K::RT(sin),K::RT(cos));


	K::Vector_3 n = rot.transform(h->facet()->normal());


	//cos betha
	cos = K::Vector_3(0, 0, 1) * xz;

	//sin betha
	orthVector = CGAL::cross_product(K::Vector_3(0, 0, 1), xz);
	sin =  sqrt(orthVector * orthVector);
	//get correct sign for sin
	if (orthVector.y()<0)
		sin = -sin;


	CGAL::Aff_transformation_3<K> rot2 (K::RT(cos),K::RT(0),K::RT(sin),
									   K::RT(0),K::RT(1),K::RT(0),
									   K::RT(-sin),K::RT(0),K::RT(cos));

	for(int i = 0; i <3; ++i){
		p_3d[i] = t.transform(p_3d[i]);
		p_3d[i] = rot.transform(p_3d[i]);
		p_3d[i] = rot2.transform(p_3d[i]);
		p[i] = K::Point_2(p_3d[i].x(), p_3d[i].y());
	}

/*
	//cos alpha
	double cos2 = h->facet()->normal() * K::Vector_3(0, 0, 1);
	double cos23 = 1 - cos2;
	//sin alpha
	K::Vector_3 orthVector2 = CGAL::cross_product(h->facet()->normal(), K::Vector_3(0, 0, 1));
	double sin2 = sqrt(orthVector * orthVector);
	K::Vector_3 u = h->facet()->normal();

	CGAL::Aff_transformation_3<K> rot3(
	K::RT(cos2+u.x()*u.x()*cos23), K::RT(u.x()*u.y()*cos23 - u.z()*sin2), K::RT(u.x()*u.z()*cos23+u.y()*sin2),
	K::RT(u.x()*u.y()*cos23+u.z()*sin2), K::RT(cos2+u.y()*u.y()*cos23), K::RT(u.y()*u.z()*cos23-u.x()*sin2),
	K::RT(u.z()*u.x()*cos23-u.y()*sin2), K::RT(u.z()*u.y()*cos23+u.x()*sin2), K::RT(cos2+u.z()*u.z()*cos23)
	);
	for(int i = 0; i <3; ++i){
		p_3d[i] = t.transform(p_3d[i]);
		p_3d[i] = rot3.transform(p_3d[i]);
		p[i] = K::Point_2(p_3d[i].x(), p_3d[i].y());
	}

*/



	//h->vertex()->point().transform(t);
	//TexturedPolyhedron::Facet::Halfedge_handle h = f->halfedge();

	/*HF_circulator h = f->facet_begin();

	TexturedPolyhedron::Plane_3 plane;
	plane = TexturedPolyhedron::Plane_3(h->vertex()->point(),
			h->next()->vertex()->point(), h->next()->next()->vertex()->point());
	cout << h->vertex()->point() << endl;
	cout << h->next()->vertex()->point() << endl;
	cout << h->next()->next()->vertex()->point() << endl;
	int i = 0;
	K::Point_3 p1[3];
	h = f->facet_begin();
	 do {
			p1[i] = plane.to_plane_basis(h->vertex()->point());
			cout << p1[i] << endl;
		 } while (++h != f->facet_begin());


	 //K::Point_3 p2 = plane.to_plane_basis(h->vertex()->point());
	//cout << p2 << endl;*/


	/*HF_circulator h = f->facet_begin();
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
	 }*/
}

void Matrix_calculator::normalise(K::Vector_3& v){
	double sq_sum = v*v;
	if(sq_sum != 0)
		v = v/sqrt(sq_sum);
}

double Matrix_calculator::calc_dt(K::Point_2* p) {
	// (x1*y2 −y1*x2) + (x2*y3 −y2*x3) + (x3*y1 −y3*x1)
	double result = p[0].x() * p[1].y() - p[0].y() * p[1].x();
	result += p[1].x() * p[2].y() - p[1].y() * p[2].x();
	result += p[2].x() * p[0].y() - p[2].y() * p[0].x();
	return result;
}

double Matrix_calculator::calc_area(TexturedPolyhedron::Face_handle& f) {
	return K::Compute_area_3()(f->halfedge()->vertex()->point(),
			f->halfedge()->next()->vertex()->point(),
			f->halfedge()->opposite()->vertex()->point());
}

void Matrix_calculator::calculate_triangle_gradient(Facet_iterator f,
		double* W) {
	// h = vertex 2; h->next = vertex 3
	HF_circulator h = f->facet_begin();
	++h;
	double height;
	for (int i = 0; i < 3; ++i) {
		//x3 - x2; x1 - x3; x2 - x1;
		W[i] = h->next()->vertex()->point().x() - h->vertex()->point().x();
		//y3 - y2; y1 - y3; y2 - y1;
		W[i + 3] = h->next()->vertex()->point().y() - h->vertex()->point().y();
		//calculate real 3D distance
		height = h->next()->vertex()->point().z() - h->vertex()->point().z();
		W[i] = W[i] * W[i] + height * height;
		W[i] = std::sqrt(W[i]);
		W[i + 3] = W[i + 3] * W[i + 3] + height * height;
		W[i + 3] = std::sqrt(W[i + 3]);
		++h;
	}
}
