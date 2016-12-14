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
	typedef TexturedPolyhedron::HalfedgeDS HalfedgeDS;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	Polyhedron P;
    K::Point_3 p( 1.0, 0.0, 0.0);
    K::Point_3 q( 0.0, 1.0, 0.0);
    K::Point_3 r( 0.0, 0.0, 1.0);
    K::Point_3 s( 0.0, 0.0, 0.0);
    P.make_tetrahedron( p, q, r, s);
    Textured_polyhedron_builder<Polyhedron, TexturedPolyhedron, K> tb;
    tb.run(P, *tp);
	//typedef Textured_Polyhedron_builder<HalfedgeDS, Polyhedron, TexturedPolyhedron, K> Textured_builder;
	//Reader r;
	//std::vector<double> coords;
	//std::vector<int> tris;
	//r.load_obj("cube.obj", coords, tris);
	//Textured_builder tb(coords, tris);
	//builds and validates polyhedron
	//tp->delegate(tb);
}

void CalculationsTest::tearDown(void){
	delete tp;
	delete mc;
}

void CalculationsTest::testTriangleGradient(void){
	/*K::Point_2 p[3];
	Matrix_calculator mc;
	tp->set_ids();
	TexturedPolyhedron::Facet_iterator f = tp->facets_begin();
	while(f->id()!=0)
		++f;
	mc.project_triangle(f, p);*/
	tp->set_ids();
	TexturedPolyhedron::Halfedge_iterator hi = tp->halfedges_begin();
	while(hi->facet()->id()!=0)
		++hi;

	cout << hi->vertex()->point() << endl;
	cout << hi->next()->vertex()->point() << endl;
	cout << hi->next()->next()->vertex()->point() << endl;
	double W[6];
	mc->calculate_triangle_gradient(hi->facet(), W);
	K::Point_2 p[3];
	tp->compute_normals_per_facet();
	mc->project_triangle(hi->facet(), p);
	for(int i = 0; i < 6; ++i)
		cout << W[i] << "  ";
	cout << endl;
	CPPUNIT_ASSERT(false);
}


