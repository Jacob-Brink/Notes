/* ReversePoem class.
 * Student Name: Jacob Brink
 * Date: 3/26/2019
 * Project: 7
 */

#ifndef REVERSEPOEM_H_
#define REVERSEPOEM_H
#include "Stack.h"

class ReversePoem {
public:
	ReversePoem(const string& filename);
	string getTitle() const;
	string getAuthor() const;
	string getBody() const;
	string getBodyReversed() const;
private:
	string myTitle, myAuthor, myBody, myBodyReversed;
};

#endif