/* Matrix.cpp defines Matrix class methods.
 * Student Name:
 * Date:
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "Matrix.h"
#include <cstdlib>

/* Default Constructor
 * Postcondition: myRows and myColumns are set to zero
 */
Matrix::Matrix() {
	myRows = myColumns = 0;
}

/* Explicit Constructor
 * Postcondition: myVec, myRows, and myColumns are set to given values
 */
Matrix::Matrix(unsigned rows, unsigned columns) {
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
const Vec<Item>& Matrix::operator[](const unsigned index) const {
	if (index < myVec.getSize()) {
		return myVec[index];
	} else {
		throw range_error("Index exceeds row count...");
	}
}

/*Subscript Operator Write
 * Returns: Non const reference to row vector
 */
Vec<Item>& Matrix::operator[](const unsigned index) {
	if (index < myVec.getSize()) {
			return myVec[index];
	} else {
		throw range_error("Index exceeds row count...");
	}
}

/* Getter Rows
 * Returns: myRows
 */
unsigned Matrix::getRows() const {
	return myRows;
}

/* Getter Columns
 * Returns: my Columns
 */
unsigned Matrix::getColumns() const {
	return myColumns;
}

/* Equality
 * Returns: true if matrices are have same dimensions and values
 */
bool Matrix::operator==(const Matrix& m2) const {
     if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
          return false;
     } else {
          return myVec == m2.myVec;
     }
 }

/* Inequality
 * Returns: NOT operator==...
 */
bool Matrix::operator!=(const Matrix& m2) const {
	return not (*this == m2);
}

/* ReadFrom
 * @params: istream
 * Precondition: The matrix object has been constructed with dimensions matching those read from in
 * Postcondition: Matrix will be populated from in
 */
void Matrix::readFrom(istream& in) {
	string input;

	for (unsigned i = 0; i < myRows; ++i) {
		for (unsigned j = 0; j < (myColumns-1); ++j) {
			getline(in, input, ' ');
			myVec[i][j] = atoi(input.c_str());
		}

		//Handle Last element which is separated by next with newline
		getline(in, input, '\n');
		myVec[i][myColumns-1] = atoi(input.c_str());
	}
}

/* WriteTo
 * @params: ostream reference
 * Precondition: none
 * Postcondition: ostream stream has Matrix values!
 */
void Matrix::writeTo(ostream& out) const{
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
 * Postcondition: Matrix contains file matrix values
 */
void Matrix::readFrom(const string& fileName) {
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
void Matrix::writeTo(const string& fileName) const {
	ofstream f(fileName.c_str());
	assert(f.is_open());

	f << myRows << ' ' << myColumns << '\n';
	writeTo(f);

	f.close();
}
