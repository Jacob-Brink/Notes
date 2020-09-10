/* ReversePoemTester class.
 * Student Name: Jacob Brink
 * Date: 3/26/2019
 * Project: 7
 */

#include <sstream>
#include "ReversePoemTester.h"
#include <fstream>

void ReversePoemTester::runTests() {
	testConstructor();
	testTitle();
	testAuthor();
	testBody();
	testBodyReversed();
}

void ReversePoemTester::testConstructor() {
	cout << "Testing ReversePoem constructor... " << flush;
	ReversePoem p("poems/cats.txt");
	cout << " 0 " << flush;
	cout << " Passed!" << endl;
}

void ReversePoemTester::testTitle() {
	cout << "Testing getTitle()... " << flush;
	ReversePoem p("poems/cats.txt");
	assert(p.getTitle() == "Cats");
	cout << " 0 " << flush;

	ReversePoem p2("poems/worstDayEver.txt");
	assert(p2.getTitle() == "Worst Day Ever?");
	cout << " 1 " << flush;
	cout << " Passed!" << endl;
}

void ReversePoemTester::testAuthor() {
	cout << "Testing getAuthor()... " << flush;
	ReversePoem p1("poems/cats.txt");
	assert(p1.getAuthor() == "Leo J. Smada");
	cout << " 0 " << flush;
	
	ReversePoem p2("poems/worstDayEver.txt");
	assert(p2.getAuthor() == "Chanie Gorkin");
	cout << " 1 " << flush;
	cout << " Passed!" << endl;
}

void ReversePoemTester::testBody() {
	cout << "Testing getBody()... " << flush;
	ReversePoem p1("poems/cats.txt");
	std::stringstream ss;
	ss << p1.getBody();
	
	ifstream fin("poems/cats.txt");
	assert( fin.is_open() );

	string strFileLine, strPoemLine;

	//remove first three lines from file stream so only body is in stream
	getline(fin, strFileLine);
	getline(fin, strFileLine);
	getline(fin, strFileLine);
	
	while(getline(fin, strFileLine)) {
		getline(ss, strPoemLine);
		assert(strFileLine == strPoemLine);
	}
	cout << " 0 " << flush;

	cout << " Passed!" << endl;
}

void ReversePoemTester::testBodyReversed() {
	cout << "Testing getBodyReversed()... " << flush;
	ReversePoem p1("poems/worstDayEver.txt");
	ifstream fin("poems/worstDayEver.txt");
	assert( fin.is_open() );

	std::stringstream ss;
	ss << p1.getBodyReversed();

	string strFileLine, strBodyLine;

	
	getline(fin, strFileLine);
	getline(fin, strFileLine);
	getline(fin, strFileLine);
	Stack<string> reverseFileBody(1);
	
	while( getline(fin, strFileLine ) ) {
		try {
			reverseFileBody.push(strFileLine);
		} catch (const StackException& se) {
			reverseFileBody.setCapacity(reverseFileBody.getCapacity()*2);
			reverseFileBody.push(strFileLine);
		}
	}
	
	unsigned i = 0;
	while ( getline(ss, strBodyLine) ) {
		assert( reverseFileBody.pop() == strBodyLine);
		cout << " " << ++i << " " << flush;
	}

	cout << " Passed!" << endl;
   
}
