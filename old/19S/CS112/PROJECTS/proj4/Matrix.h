/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name:
 * Date:
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vec.h"

typedef double Item;

class Matrix {
public:
	Matrix();
	Matrix(unsigned rows, unsigned columns);
	unsigned getRows() const;
	unsigned getColumns() const;

	const Vec<Item>& operator[](const unsigned index) const;
	Vec<Item>& operator[](const unsigned index);
	bool operator==(const Matrix& m2) const;
	bool operator!=(const Matrix& m2) const;

	void readFrom(istream& in);
	void readFrom(const string& fileName);
	void writeTo(ostream& out) const;
	void writeTo(const string& fileName) const;

private:
	unsigned myRows;
	unsigned myColumns;
	Vec< Vec<Item> > myVec;
	friend class MatrixTester;
};


#endif
