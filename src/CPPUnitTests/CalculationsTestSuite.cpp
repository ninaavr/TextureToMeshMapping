/*
 * CalculationsTestSuite.cpp
 *
 *  Created on: 8 Dec 2016
 *      Author: osboxes
 */

#include "CalculationsTestSuite.h"

void CalculationsTest::setUp(void){
	tp = new TexturedPolyhedron();
	mc = new Matrix_calculator();
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	Polyhedron P;
    K::Point_3 p( 1.0, 0.0, 0.0);
    K::Point_3 q( 0.0, 1.0, 0.0);
    K::Point_3 r( 0.0, 0.0, 1.0);
    K::Point_3 s( 0.0, 0.0, 0.0);
    P.make_tetrahedron( p, q, r, s);
    Textured_polyhedron_builder<Polyhedron, TexturedPolyhedron, K> tb;
    tb.run(P, *tp);
    tp->set_ids();
    tp->compute_normals_per_facet();
}

void CalculationsTest::tearDown(void){
	delete tp;
	delete mc;
}

void CalculationsTest::testLengthPreservation(void){
	bool is_equal = true;
	TexturedPolyhedron::Face_iterator f;
	double W[6];
	double length, length2;
	for(f = tp->facets_begin(); f != tp->facets_end(); ++f){
		int i = 0;
		TexturedPolyhedron::Halfedge_around_facet_circulator h = f->facet_begin();
		//cout << h->vertex()->point() << endl;
		//cout << h->next()->vertex()->point() << endl;
		//cout << h->next()->next()->vertex()->point() << endl;
		mc->calc_W(f, W);
		do{
			K::Vector_3 v = h->next()->next()->vertex()->point() - h->next()->vertex()->point();
			length = sqrt(v.x()*v.x() + v.y()*v.y() + v.z()*v.z());
			length2 = sqrt(W[i]*W[i] + W[i + 3]*W[i + 3]);
			is_equal = (is_equal && (abs(length - length2) < 0.000001));
			++i;
		}while (++h != f->facet_begin());
	}
	CPPUNIT_ASSERT(is_equal);
}

void CalculationsTest::testOrientation(void){
	//p1, p2, p3 are the 3 vertices of a facet (given in counterclockwise order by CGAL library)
	//we check if after transformation the 2D triangle contains them in the same order
	//if that is true, then all 2D triangles have preserved their orientation as it was
	//looked "outside" of the mesh
	bool is_correct = true;
	double W[6];
	TexturedPolyhedron::Face_iterator f;
	for(f = tp->facets_begin(); f != tp->facets_end(); ++f){
		mc->calc_W(f, W);
		//p2.x - p1.x > 0, hence p2 is to the right of p1
 		is_correct = is_correct && (W[2] > 0);
 		//p1.y - p3.y < 0, hence p3 is above p1
		is_correct = is_correct && (W[4] < 0);
		//p3.y - p2.y > 0, hence p3 is above p2
		is_correct = is_correct && (W[3] > 0);
	}
	CPPUNIT_ASSERT(is_correct);
}

void CalculationsTest::testCalculationForVertex(void){
	bool is_equal = true;
	TexturedPolyhedron::Face_iterator f;
	TexturedPolyhedron::Vertex_handle v;
	double W[6];
	double W2[2];
	for(f = tp->facets_begin(); f != tp->facets_end(); ++f){
		int i = 0;
		TexturedPolyhedron::Halfedge_around_facet_circulator h = f->facet_begin();
		mc->calc_W(f, W);
		do{
			v = h->vertex();
			mc->calc_W(f, v, W2);
			is_equal = is_equal && (W[i] == W2[0]);
			is_equal = is_equal && (W[i + 3] == W2[1]);
			++i;
		}while (++h != f->facet_begin());
	}
	CPPUNIT_ASSERT(is_equal);
}
