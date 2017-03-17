/*
 * SeamPinnedTestSuite.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: ninaavr
 */

#include "SeamPinnedTestSuite.h"

void TestSeamAndPinn::setUp(void){
	tp = new TexturedPolyhedron();
	fml = new Free_matrix_loader();
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
	tp->compute_normals_per_facet();
}



void TestSeamAndPinn::tearDown(void){
	delete tp;
	delete fml;
}

void TestSeamAndPinn::testPinnedSize(void){
	TexturedPolyhedron::Halfedge_iterator hi = tp->halfedges_begin();
	std::list<TexturedPolyhedron::Halfedge_handle> seam_list;
	seam_list.push_back(hi);
	++hi; ++hi;
	seam_list.push_back(hi);
	tp->set_seam(seam_list);
	++hi;++hi;
	hi->vertex()->u()[0] = 0.1;
	hi->vertex()->v()[0] = 0.1;
	Eigen::SparseMatrix<double> Mf;
	fml->load_M(*tp, Mf);
	//cout << endl << tp->size_of_vertices() << endl;
	//cout << Mf.cols() << endl;
	CPPUNIT_ASSERT(Mf.cols() == 2*((int)tp->size_of_vertices() + 1 - 1));
}

void TestSeamAndPinn::testSeamSize(void){
	std::list<TexturedPolyhedron::Halfedge_handle> seam_list;
	TexturedPolyhedron::Halfedge_iterator hi = tp->halfedges_begin();
	seam_list.push_back(hi);
	hi = hi->next_on_vertex()->opposite();
	seam_list.push_back(hi);
	tp->set_seam(seam_list);
	CPPUNIT_ASSERT(tp->seam->size()==2);
}
