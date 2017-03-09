/*
 * LoadingTestSuite.h
 *
 *  Created on: 18 Dec 2016
 *      Author: ninaavr
 */

/*#ifndef LOADINGTESTSUITE_H_
#define LOADINGTESTSUITE_H_

#include <cppunit/extensions/HelperMacros.h>

#include "../TexturedPolyhedron/Textured_polyhedron.h"
#include "../PolyhedronBuilder/Textured_polyhedron_builder.h"
#include "../Free_matrix_loader.h"
#include "../Pinned_matrix_loader.h"
#include "../IO/Reader.h"

using namespace CppUnit;
using namespace std;
using namespace Eigen;

class LoadingTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE(LoadingTest);
	CPPUNIT_TEST(testFreeLoading);
	CPPUNIT_TEST(testPinnedLoading);
	CPPUNIT_TEST_SUITE_END();

private:
	typedef CGAL::Simple_cartesian<double> K;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
	typedef TexturedPolyhedron::HalfedgeDS HalfedgeDS;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	typedef Textured_Polyhedron_builder<HalfedgeDS, Polyhedron, TexturedPolyhedron, K> Textured_builder;

	TexturedPolyhedron* tp;
	Matrix_calculator* mc;
	Free_matrix_loader* fml;
	Pinned_matrix_loader* pml;
	Eigen::SparseMatrix<double>* M;
	std::list<TexturedPolyhedron::Halfedge_handle>* seam;
	std::list<TexturedPolyhedron::Vertex_handle>* pinned;

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testFreeLoading(void);
	void testPinnedLoading(void);
};

#endif /* LOADINGTESTSUITE_H_ */
