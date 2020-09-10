/* Vec.h provides a simple vector class named Vec.
 * Student Name: Jacob Brink
 * Date: 2/19/2019
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
using namespace std;

typedef double Item;

class Vec {
public:
	Vec();
	Vec(unsigned size);
	virtual ~Vec();
	void makeCopyOf(const Vec& orginal);
	Vec(const Vec& original);

	//overloads
	Vec& operator=(const Vec& original);
	bool operator==(const Vec& v2) const;

	Item& operator[](unsigned index);
	Item const operator[](unsigned index) const;

	bool operator!=(const Vec& original) const;

	Vec operator+(const Vec& other) const;
	Vec operator-(const Vec& other) const;
	Item operator*(const Vec& other) const;

	//getter methods
	unsigned getSize() const { return mySize; };
	Item getItem(unsigned index) const;

	//Set methods
	void setItem(unsigned index, const Item& it);
	void setSize(unsigned newSize);

	//stream methods
	void writeTo(ostream& out) const;
	void writeTo(const string fileName) const;
	void readFrom(istream& in);
	void readFrom(const string fileName);



private:
	unsigned mySize;
	Item * myArray;
	friend class VecTester;
};

#endif /*VEC_H_*/
