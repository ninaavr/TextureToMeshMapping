/*
 * LoadingTestSuite.cpp
 *
 *  Created on: 18 Dec 2016
 *      Author: ninaavr
 */
/*
#include "LoadingTestSuite.h"

void LoadingTest::setUp(void){
	tp = new TexturedPolyhedron();
	fml = new Free_matrix_loader();
	pml = new Pinned_matrix_loader();
    M = new Eigen::SparseMatrix<double>;
    seam = new std::list<TexturedPolyhedron::Halfedge_handle>;
    pinned = new std::list<TexturedPolyhedron::Vertex_handle>;
	Reader r;
	std::vector<double> coords;
	std::vector<int> tris;
	r("cube.obj", coords, tris);
	Textured_builder tb(coords, tris);
	//builds and validates polyhedron
	tp->delegate(tb);
    tp->set_ids();
    tp->compute_normals_per_facet();

    TexturedPolyhedron::Halfedge_iterator hi = tp->halfedges_begin();
    //sets 3 seam halfedges, i.e. 2 seam vertices, 1 of them also pinned
    pinned->push_back(hi->opposite()->vertex());
    seam->push_back(hi);
    hi = hi->next_on_vertex()->opposite();
    pinned->push_back(hi->vertex());
   	seam->push_back(hi);
   	hi = hi->next_on_vertex()->opposite();
   	seam->push_back(hi);
   	tp->set_seam(*seam);
}

void LoadingTest::tearDown(void){
	delete tp;
	delete fml;
	delete seam;
	delete pinned;
}

void LoadingTest::testFreeLoading(void){
	fml->load_M(*tp, *pinned, *M);
	//use matrix which counts inserted elements in each row (also equal 0)
	Eigen::SparseMatrix<double, RowMajor> M2 = *M;
	int numPinned1 = 0;
	int numPinned2 = 0;
	for (int i = 0; i < M2.rows() / 2; ++i){
		//cout << "non zeros    "<< M2.row(i).nonZeros() << endl;
		//numPinned are facets with pinned vertices, facets with e.g. 2 pinned vertices are counted twice
		if (M2.row(i).nonZeros()==0)
			numPinned1 += 3;
		else if (M2.row(i).nonZeros()==1)
			numPinned1 += 2;
		else if (M2.row(i).nonZeros()==2)
			++numPinned1;
		//facets can have 0, 1, 2 or 3 free vertices
		else if (M2.row(i).nonZeros()!=3)
			CPPUNIT_ASSERT(false);

		//repeat for botom half of the matrix
		if (M2.row(i + tp->size_of_facets()).nonZeros()==0)
			numPinned2 += 3;
		else if (M2.row(i + tp->size_of_facets()).nonZeros()==1)
			numPinned2 += 2;
		else if (M2.row(i + tp->size_of_facets()).nonZeros()==2)
			++numPinned2;
		//facets can have 0, 1, 2 or 3 free vertices
		else if (M2.row(i + tp->size_of_facets()).nonZeros()!=3)
			CPPUNIT_ASSERT(false);

	}
	//checks number of facets with 2 free vertices
	int numPinned = 0;
	typename std::list<TexturedPolyhedron::Vertex_handle>::iterator it;
	for(it = pinned->begin(); it != pinned->end(); ++it){
		numPinned += (*it)->degree();
	}
	CPPUNIT_ASSERT(numPinned == numPinned1);
	CPPUNIT_ASSERT(numPinned == numPinned2);
}

void LoadingTest::testPinnedLoading(void){
	pml->load_M(*tp, *pinned, *M);
	Eigen::SparseMatrix<double, RowMajor> M2 = *M;
	//counts number of facets with pinned vertices, facets with e.g. 2 pinned vertices are counted twice
	//check top and bottom half of the matrix
	int numPinned1 = 0;
	int numPinned2 = 0;
	for (int i = 0; i < M2.rows() / 2; ++i){
		numPinned1 += M2.row(i).nonZeros();
		numPinned2 += M2.row(i + tp->size_of_facets()).nonZeros();
	}
	int numPinned = 0;
	typename std::list<TexturedPolyhedron::Vertex_handle>::iterator it;
	for(it = pinned->begin(); it != pinned->end(); ++it){
		numPinned += (*it)->degree();
	}
	CPPUNIT_ASSERT(numPinned1 == numPinned);
	CPPUNIT_ASSERT(numPinned2 == numPinned);
}
*/
