/* ReversePoemTester class.
 * Student Name: Jacob Brink
 * Date: 3/26/2019
 * Project: 7
 */

#ifndef REVERSEPOEMTESTER_H_
#define REVSERSEPOEMTESTER_H_
#include "ReversePoem.h"
#include <cassert>

class ReversePoemTester {
public:
	void runTests();
	void testConstructor();
	void testTitle();
	void testAuthor();
	void testBody();
	void testBodyReversed();
};

#endif /*REVERSEPOEMTESTER_H_*/
