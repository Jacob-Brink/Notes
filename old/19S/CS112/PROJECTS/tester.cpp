/* tester.cpp is a "driver" to run the tests in the StackTester class.
 * Joel Adams, for CS 112 at Calvin College.
 */
 
#include "StackTester.h"
#include "ReversePoemTester.h"

int main() {
	StackTester st;
	st.runTests();
	ReversePoemTester rpt;
	rpt.runTests();
}

