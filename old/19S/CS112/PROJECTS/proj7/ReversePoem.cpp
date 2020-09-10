/* ReversePoem class.
 * Student Name: Jacob Brink
 * Date: 3/26/2019
 * Project: 7
 */

#include <fstream> // opening files
#include "ReversePoem.h"
#include <cassert>

/* constructor
 * Parameter: filename
 * Precondition: file exists
 * Postcondition: myTitle, myAuthor, myBody, myBodyReversed are populated
 */
ReversePoem::ReversePoem(const string& filename) {
	myBody = myBodyReversed = "";
	ifstream fin(filename.c_str());
	assert( fin.is_open() );
	string blank, line;
	//get title
	getline(fin, myTitle);

	//get author
	getline(fin, myAuthor);

	//get blank line
	getline(fin, blank);

	//read body into stack
	Stack<string> readStack(1);
	while(getline(fin, line)) {
		try {
			myBody += line;
			myBody += "\n";
			readStack.push(line);
		} catch (const StackException& se) {
			readStack.setCapacity(readStack.getCapacity()*2);
			readStack.push(line);
		}
	}

	while(true) {
		try {
			myBodyReversed += readStack.pop();
			myBodyReversed += "\n";
		} catch (const StackException& se) {
			break;
		}
	}
	fin.close();
}

/* gets myTitle
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: myTitle
 */
string ReversePoem::getTitle() const {
	return myTitle;
}

/* gets myAuthor
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: myAuthor
 */
string ReversePoem::getAuthor() const {
	return myAuthor;
}

/* gets myBody
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: myBody
 */
string ReversePoem::getBody() const {
	return myBody;
}


/* gets myBodyReversed
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: myBodyReversed
 */
string ReversePoem::getBodyReversed() const {
	return myBodyReversed;
}
