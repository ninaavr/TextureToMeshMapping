/*
 * Runner.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: ninaavr
 */

#include <iostream>

#include "cppunit/TestSuite.h"
#include <cppunit/ui/text/TestRunner.h>

using namespace std;
using namespace CppUnit;

/** run given test
 * @param tc test case meant to be run */
int run (Test* t) {
	TextUi::TestRunner runner;

	cout << "Creating Test Suites:" << endl;
	runner.addTest(t);
	cout<< "Running the unit tests."<<endl;
	runner.run();

	return 0;
}

