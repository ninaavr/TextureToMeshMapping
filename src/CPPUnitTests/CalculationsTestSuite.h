/*
 * CalculationsTestSuite.h
 *
 *  Created on: 8 Dec 2016
 *      Author: ninaavr
 */

#ifndef CALCULATIONSTESTSUITE_H_
#define CALCULATIONSTESTSUITE_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <stdlib.h>

#include "../TexturedPolyhedron/Textured_polyhedron.h"
#include "../PolyhedronBuilder/Textured_polyhedron_builder.h"
#include "../PolyhedronBuilder/Textured_polyhedron_builder_from_polyhedron.h"
#include "../Free_matrix_loader.h"
#include "../IO/Reader.h"

using namespace CppUnit;
using namespace std;

class CalculationsTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE(CalculationsTest);
	CPPUNIT_TEST(testTriangleGradient);
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
	void testTriangleGradient(void);
};

#endif /* CALCULATIONSTESTSUITE_H_ */
