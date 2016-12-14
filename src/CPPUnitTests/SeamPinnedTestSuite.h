/*
 * SeamPinnedTestSuite.h
 *
 *  Created on: 4 Dec 2016
 *      Author: ninaavr
 */

#ifndef SEAMPINNEDTESTSUITE_H_
#define SEAMPINNEDTESTSUITE_H_

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
#include "../TexturedPolyhedron/Textured_polyhedron.h"
#include "../PolyhedronBuilder/Textured_polyhedron_builder.h"
#include "../Free_matrix_loader.h"
#include "../IO/Reader.h"

using namespace CppUnit;
using namespace std;
class TestSeamAndPinn: public CppUnit::TestCase


{
CPPUNIT_TEST_SUITE(TestSeamAndPinn);

	CPPUNIT_TEST(testPinnedSize);
	CPPUNIT_TEST(testSeamSize);
	CPPUNIT_TEST_SUITE_END();

private:
	typedef CGAL::Simple_cartesian<double> K;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
	TexturedPolyhedron* tp;
	Free_matrix_loader* ml;

public:

	void setUp(void);
	void tearDown(void);

protected:

	void testPinnedSize(void);
	void testSeamSize(void);

};
#endif /* SEAMPINNEDTESTSUITE_H_ */
