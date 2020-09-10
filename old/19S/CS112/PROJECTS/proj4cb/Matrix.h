/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name:
 * Date:
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include "Matrix.h"
#include "Vec.h"
#include <cstdlib>

template<class Item>
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
	Matrix operator+(const Matrix& m2) const;
	Matrix operator-(const Matrix& m2) const;
	Matrix getTranspose();

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

/* Default Constructor
 * Postcondition: myRows and myColumns are set to zero
 */
template<class Item>
Matrix<Item>::Matrix() {
	myRows = myColumns = 0;
}

/* Explicit Constructor
 * Postcondition: myVec, myRows, and myColumns are set to given values
 */
template<class Item>
Matrix<Item>::Matrix(unsigned rows, unsigned columns) {
	myRows = rows;
	myColumns = columns;
	myVec.setSize(rows);
	for (unsigned i = 0; i < rows; ++i) {
		myVec[i].setSize(columns);
	}
}

/* Subscript Operator Read
 * Returns: Row Vector
 */
template<class Item>
const Vec<Item>& Matrix<Item>::operator[](const unsigned index) const {
	if (index < myVec.getSize()) {
		return myVec[index];
	} else {
		throw range_error("Index exceeds row count...");
	}
}

/* Subscript Operator Write
 * Returns: Non const reference to row vector
 */
template<class Item>
Vec<Item>& Matrix<Item>::operator[](const unsigned index) {
	if (index < myVec.getSize()) {
        return myVec[index];
	} else {
		throw range_error("Index exceeds row count...");
	}
}

/* Getter Rows
 * Returns: myRows
 */
template<class Item>
unsigned Matrix<Item>::getRows() const {
	return myRows;
}

/* Getter Columns
 * Returns: my Columns
 */
template<class Item>
unsigned Matrix<Item>::getColumns() const {
	return myColumns;
}

/* Equality
 * Returns: true if matrices are have same dimensions and values
 */
template<class Item>
bool Matrix<Item>::operator==(const Matrix& m2) const {
     if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
          return false;
     } else {
          return myVec == m2.myVec;
     }
 }

/* Inequality
 * Returns: NOT operator==...
 */
template<class Item>
bool Matrix<Item>::operator!=(const Matrix& m2) const {
	return not (*this == m2);
}

/* ReadFrom
 * @params: istream
 * Precondition: The matrix object has been constructed with dimensions matching those read from in
 * Postcondition: Matrix<Item> will be populated from in
 */
template<class Item>
void Matrix<Item>::readFrom(istream& in) {
	string input;

	for (unsigned i = 0; i < myRows; ++i) {
		for (unsigned j = 0; j < myColumns; ++j) {
			in >> myVec[i][j];
		}
	}
}

/* WriteTo
 * @params: ostream reference
 * Precondition: none
 * Postcondition: ostream stream has Matrix<Item> values!
 */
template<class Item>
void Matrix<Item>::writeTo(ostream& out) const{
	for (unsigned i = 0; i < myRows; ++i) {
		for (unsigned j = 0; j < (myColumns-1); ++j) {
			out << myVec[i][j] << ' ';
		}
		out << myVec[i][myColumns-1] << '\n';
	}
}

/* Read From File
 * @params: fileName
 * Precondition: file must exist and contain values of dimension in first line and values on the rest of the lines
 * Postcondition: Matrix<Item> contains file matrix values
 */
template<class Item>
void Matrix<Item>::readFrom(const string& fileName) {
	ifstream f(fileName.c_str());
	assert(f.is_open());

	f >> myRows >> myColumns;

	myVec.setSize(myRows);
	for (unsigned i = 0; i < myRows; ++i) {
		myVec[i].setSize(myColumns);
	}
	readFrom(f);
	f.close();
}

/* Writes to file
 * @params: fileName
 * Postcondition: the file exists with given name and has values and dimensions of matrix
 */
template<class Item>
void Matrix<Item>::writeTo(const string& fileName) const {
	ofstream f(fileName.c_str());
	assert(f.is_open());

	f << myRows << ' ' << myColumns << '\n';
	writeTo(f);

	f.close();
}

/* Addition Overload
 * @params: const ref Matrix<Item> object
 * Precondition: the two matrices are of same dimensiosn
 * Returns: Added matrix
 */
template<class Item>
Matrix<Item> Matrix<Item>::operator+(const Matrix& m2) const {
    if ((myRows == m2.getRows()) && (myColumns == m2.getColumns())) {

        Matrix<Item> newMatrix(myRows, myColumns);

        for (unsigned i = 0; i < myRows; ++i) {
            for (unsigned j = 0; j < myColumns; ++j) {
                newMatrix[i][j] = myVec[i][j] + m2[i][j];
            }
        }
        return newMatrix;

    } else {
        throw invalid_argument("Matrices must be of same dimensions.");
    }
};

/* Subtraction Overload
 * @params: const ref Matrix<Item> object
 * Precondition: the two matrices are of same dimensiosn
 * Returns: Difference matrix
 */
template<class Item>
Matrix<Item> Matrix<Item>::operator-(const Matrix& m2) const {
    if ((myRows == m2.getRows()) && (myColumns == m2.getColumns())) {

        Matrix<Item> newMatrix(myRows, myColumns);

        for (unsigned i = 0; i < myRows; ++i) {
            for (unsigned j = 0; j < myColumns; ++j) {
                newMatrix[i][j] = myVec[i][j] - m2[i][j];
            }
        }
        return newMatrix;

    } else {
        throw invalid_argument("Matrices must be of same dimensions.");
    }
}

/* Transpose
 * @params: none
 * Precondition: none
 * Returns: Matrix<Item> with rows and columns switched.
 */
template<class Item>
Matrix<Item> Matrix<Item>::getTranspose() {
    Matrix<Item> newMatrix(myColumns, myRows);

    for (unsigned i = 0; i < myColumns; ++i) {
        for (unsigned j = 0; j < myRows; ++j) {
            newMatrix[i][j] = myVec[j][i];
        }
    }

    return newMatrix;
}

#endif
