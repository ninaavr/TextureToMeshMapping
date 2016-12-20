/*
 * CalculationsTestSuite.h
 *
 *  Created on: 8 Dec 2016
 *      Author: ninaavr
 */

#ifndef CALCULATIONSTESTSUITE_H_
#define CALCULATIONSTESTSUITE_H_

#include <cppunit/extensions/HelperMacros.h>

#include "../TexturedPolyhedron/Textured_polyhedron.h"
#include "../PolyhedronBuilder/Textured_polyhedron_builder_from_polyhedron.h"
#include "../Free_matrix_loader.h"

using namespace CppUnit;
using namespace std;

class CalculationsTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE(CalculationsTest);
	CPPUNIT_TEST(testLengthPreservation);
	CPPUNIT_TEST(testOrientation);
	CPPUNIT_TEST(testCalculationForVertex);
	CPPUNIT_TEST_SUITE_END();

private:
	typedef CGAL::Simple_cartesian<double> K;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
	TexturedPolyhedron* tp;
	Matrix_calculator* mc;

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testLengthPreservation(void);
	void testOrientation(void);
	void testCalculationForVertex(void);
};

#endif /* CALCULATIONSTESTSUITE_H_ */
