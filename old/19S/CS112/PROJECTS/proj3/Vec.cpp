/* Vec.cpp defines the methods for Vec, a simple vector class.
 * Student Name: Jacob Brink
 * Date: 2/19/2019
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#include "Vec.h"
#include <stdexcept>
#include <fstream>      // ifstream, ofstream, ...
#include <cassert>

/* Vec Default Constructor
 */

Vec::Vec() {
	mySize = 0;
	myArray = NULL;
}

/* Vec Default Constructor
 * @param: unsigned size
 * Precondition: size given is positive or zero
 * Postcondition: mySize is set to size if valid, and myArray is set to Null for size 0 and to new allocation for size > 0
 */
Vec::Vec(unsigned size) {
	myArray = NULL;
	if(size > 0) {
		mySize = size;
		myArray = new Item[size]();
	} else if (size == 0) {
		mySize = 0;
		myArray = NULL;
	} else {
		throw range_error("Cannot set vector to negative size");
	}
}

/* Set Values to Given Vec
 * @param: const reference vector
 * Postcondition: Values match that of original
 */
void Vec::makeCopyOf(const Vec& original) {
    //Set mySize to original and default myArray = NULL
	mySize = original.mySize;
	myArray = NULL;

	if (mySize > 0) {
		myArray = new Item[mySize]();
		for (unsigned i = 0; i < mySize; ++i) {
			myArray[i] = original.myArray[i];
		}
	}
}

/* Vec Copy Constructor
 * @param: Reference to original Vec
 * Postcondition: Vec constructed has exact same values for size and elements of array
 */
Vec::Vec(const Vec& original) {
	makeCopyOf(original);
}

/* Assignment Operator
 * @param: Reference to original Vec to be copied from
 * Return: Returns Vec that has exact same values for size and elements of array of original
 */
Vec& Vec::operator=(const Vec& original) {

	if (this != &original) {
        delete [] myArray;
		myArray = NULL;
        makeCopyOf(original);

	}

	return *this;
}

/* Set Item Method
 * @param: index which must be within bounds of array range, and reference to Item
 * Precondition: Vec must have mySize greater than 0
 * Postcondition: Element with given index in array is assigned given Item
 */
void Vec::setItem(unsigned index, const Item& it) {
	if (mySize == 0) {
		throw range_error("Cannot set value on empty array.");
	} else if (index > (mySize-1)) {
		throw range_error("Index out of bounds.");
	} else {
		myArray[index] = it;
	}
}

/* Get Item Method
 * @param: index which must be within bounds of array range
 * Precondition: Vec must have mySize greater than 0
 * Return: Element with given index in array is assigned given Item
 */

Item Vec::getItem(unsigned index) const {
	if (mySize == 0) {
		throw range_error("Cannot set value on empty array.");
	} else if (index > (mySize-1)) {
		throw range_error("Index out of bounds.");
	} else {
		return myArray[index];
	}
}

/* Set Size Method
 * @param: unsigned newSize
 * Postcondition: myArray will have size newSize, with old values saved when possible
 */
void Vec::setSize(unsigned newSize) {
	if (newSize == 0) {
		delete [] myArray;
		myArray = NULL;
	} else if (newSize < mySize) {
		Item * newArray = new Item[newSize]();
		for (unsigned i = 0; i < newSize; ++i) {
			newArray[i] = myArray[i];
		}
		delete [] myArray;
		myArray = newArray;
	} else if (newSize > mySize) {
		Item * newArray = new Item[newSize]();
		for (unsigned i = 0; i < mySize; ++i) {
			newArray[i] = myArray[i];
		}
		for (unsigned i = mySize; i < newSize; ++i) {
			newArray[i] = Item();
		}
		delete [] myArray;
		myArray = newArray;
	}

	mySize = newSize;

}

/* Boolean Equality
 * @param: const reference to compared value
 * Return: true if values of both Vec's arrays are equal and size is equal
 */
bool Vec::operator==(const Vec& v2) const {
	if (mySize == v2.getSize()) {
		for (unsigned i = 0; i < mySize; ++i) {
			if (myArray[i] != v2.getItem(i)) {
				return false;
			}
		}
	} else {
		return false;
	}

	return true;
}

/* Write To Ostream
 * @param: ostream reference
 * Postcondition: given ostream is populated with values from Vec's array
 */
void Vec::writeTo(ostream& out) const {
	//Loop to send each element except last to ostream with space appended
	for (unsigned i = 0; i < mySize-1; ++i) {
		out << myArray[i] << " ";
	}
	//Do last element without space appended
	out << myArray[mySize-1];
}

/* Read From Istream
 * @param: istream reference
 * Postcondition: Vec is populated with data from istream
 */
void Vec::readFrom(istream& in) {
	for (unsigned i = 0; i < mySize; ++i) {
		in >> myArray[i];
	}
}

/* Returns reference to Item, allowing for assignment
 * Returns: reference to myArray[index] if valid, otherwise throw exception
 */
Item& Vec::operator[](unsigned index) {
	if (mySize == 0) {
		throw range_error("Cannot index empty Vec...");
	} else if (index > (mySize-1)) {
		throw range_error("Index is out of bounds...");
	} else {
		return myArray[index];
	}
}

/* Returns Immutable Item by index
 * Returns: see getItem(index)
 */
Item const Vec::operator[](unsigned index) const{
	return getItem(index);
}

/* Return Inequality
 * Returns: opposite of equality operator, see equality operator
 */
bool Vec::operator!=(const Vec& original) const {
	return not (original == *this);
}

/* Read From
 * @params: filenameVec const operator+(const Vec& Vec1, const Vec& Vec2);
 * Precondition: file exists
 * Postcondition: Vec contains elements described in file.
 */
void Vec::readFrom(const string fileName) {
    ifstream fin(fileName.c_str());
    assert(fin.is_open());

    Item inputItem;
    string inputString;

    getline(fin, inputString);
    setSize(stod(inputString.c_str()));

    for(unsigned i = 0; i < mySize; ++i) {
        fin >> inputString;
        inputItem = stod(inputString.c_str());
        setItem(i, inputItem);
    }

    fin.close();
}

/* Read From
 * @params: filename
 * Precondition: none
 * Postcondition: file contains number of vec values and values.
 */
void Vec::writeTo(const string fileName) const{
    ofstream fout(fileName.c_str());
    assert(fout.is_open());

    fout << mySize;

    for (unsigned i = 0; i < mySize; ++i) {
        fout << '\n' << myArray[i];
    }

    fout.close();
}

/* Addition Overloading
 * @params: other vector
 * Precondition: Both are of same size
 * Returns: returns vector sum
 */
Vec Vec::operator+(const Vec& other) const {
    if (mySize == other.getSize()) {
        Vec sumVector(mySize);
        for (unsigned i = 0; i < mySize; ++i) {
            sumVector[i] = myArray[i] + other[i];
        }
        return sumVector;
    } else {
        throw invalid_argument("Vectors should be same size...");
    }

};

/* Subtraction Overloading
 * @params: other vector
 * Precondition: Both are of same size
 * Returns: returns vector difference
 */
Vec Vec::operator-(const Vec& other) const {
    if (mySize == other.getSize()) {
        Vec sumVector(mySize);
        for (unsigned i = 0; i < mySize; ++i) {
            sumVector[i] = myArray[i] - other[i];
        }
        return sumVector;
    } else {
        throw invalid_argument("Vectors should be same size...");
    }

};

/* Dot Product
 * @params: other vector
 * Precondition: Both are of same size
 * Returns: returns vector dotProduct of type Item
 */
Item Vec::operator*(const Vec& other) const {
    if (mySize == other.mySize) {
        Item dProd = 0;
        for (unsigned i = 0; i < mySize; ++i) {
            dProd += other[i]*myArray[i];
        }
        return dProd;
    } else {
        throw invalid_argument("Vectors should be same size...");
    }
}

/* Vec Destructor
 * @param: none
 * Postcondition: Vec myArray is deallocated and is set to Null, mySize set to 0
 */
Vec::~Vec() {
	delete [] myArray;
	myArray = NULL;
	mySize = 0;
}
