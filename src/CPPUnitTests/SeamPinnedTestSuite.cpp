/*
 * SeamPinnedTestSuite.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: osboxes
 */

#include "SeamPinnedTestSuite.h"

void TestSeamAndPinn::setUp(void){
	tp = new TexturedPolyhedron();
	ml = new Free_matrix_loader();
	typedef TexturedPolyhedron::HalfedgeDS HalfedgeDS;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	typedef Textured_Polyhedron_builder<HalfedgeDS, Polyhedron, TexturedPolyhedron, K> Textured_builder;
	Reader r;
	std::vector<double> coords;
	std::vector<int> tris;
	r("cube.obj", coords, tris);
	Textured_builder tb(coords, tris);
	//builds and validates polyhedron
	tp->delegate(tb);
}



void TestSeamAndPinn::tearDown(void){
	delete tp;
	delete ml;
}

void TestSeamAndPinn::testPinnedSize(void){
	TexturedPolyhedron::Halfedge_iterator hi = tp->halfedges_begin();
	++hi;
	std::list<TexturedPolyhedron::Vertex_handle> pv, pf;
	pv.push_back(hi->vertex());
	ml-> get_free_vertices(*tp, pv, pf);
	CPPUNIT_ASSERT(pf.size()==7);
}

void TestSeamAndPinn::testSeamSize(void){
	std::list<TexturedPolyhedron::Halfedge_handle> seam_list;
	TexturedPolyhedron::Halfedge_iterator hi = tp->halfedges_begin();
	seam_list.push_back(hi);
	hi++;
	seam_list.push_back(hi);
	tp->set_seam(seam_list);
	CPPUNIT_ASSERT(tp->seam->size()==2);
}

