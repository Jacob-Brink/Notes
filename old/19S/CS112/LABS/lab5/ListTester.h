/* ListTester.h declares the test-class for class List.
 * Student: Jacob Brink
 * Date: 3/5/2019
 * By: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef LISTTESTER_H_
#define LISTTESTER_H_

class ListTester {
public:
	void runTests();
	void testDefaultConstructor();
	void testNodeDefaultConstructor();
	void testNodeExplicitConstructor();
	void testAppend();
	void testDestructor();
	void testCopyConstructor();
	void testAssignment();

};

#endif /*LISTTESTER_H_*/
