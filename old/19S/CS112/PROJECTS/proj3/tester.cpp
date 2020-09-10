/* tester.cpp drives the testing of our Vec class.
 * Student Name: Jacob Brink
 * Date: 2/19/2019
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#include "VecTester.h"
#include "Application.h"

int main() {
	VecTester vt;
	vt.runTests();
	Application app;
	app.run();
}
