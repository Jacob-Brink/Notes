/* Vec<Item>.h provides a simple Vec<Item>tor class named Vec<Item>.
 * Student Name: Jacob Brink, Joe Joel (Unless otherwise stated, all declarations and definitions are by default written by Jacob Brink)
 * Date: 2/19/2019
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#ifndef Vec_H_
#define Vec_H_

#include <iostream>
#include <stdexcept>
#include <fstream>      // ifstream, ofstream, ...
#include <cassert>
#include <cstdlib>

using namespace std;

template<class Item>
class Vec {
public:

	Vec();
	Vec(unsigned size);
	virtual ~Vec();
	void makeCopyOf(const Vec<Item>& orginal);
	Vec(const Vec<Item>& original);

	//overloads
	Vec& operator=(const Vec<Item>& original);
	bool operator==(const Vec<Item>& v2) const;

	Item& operator[](unsigned index);
	//Item const operator[](unsigned index) const;

	bool operator!=(const Vec<Item>& original) const;

	Vec operator+(const Vec<Item>& other) const;
	//Vec operator-(const Vec<Item>& other) const;

	//Item operator*(const Vec<Item>& other) const;

	//getter methods
	unsigned getSize() const { return mySize; };
	Item getItem(unsigned index) const;

	//Set methods
	void setItem(unsigned index, const Item& it);
	void setSize(unsigned newSize);

	//stream methods
	//void writeTo(ostream& out) const;
	//void writeTo(const string fileName) const;
	void readFrom(istream& in);
	void readFrom(const string fileName);

	//Joe Joel Method Prototypes
	Vec operator-(const Vec<Item>& v2);
	double operator*(const Vec<Item>& v2);
	void writeTo(const string fileName);
	void writeTo(ostream& out) const;
	const Item& operator[](const unsigned index) const;



private:
	unsigned mySize;
	Item * myArray;
	friend class VecTester;

};


/* Vec<Item> Default Constructor
 */
template<class Item>
Vec<Item>::Vec() {
	mySize = 0;
	myArray = NULL;
}

/* Vec<Item> Default Constructor
 * @param: unsigned size
 * Precondition: size given is positive or zero
 * Postcondition: mySize is set to size if valid, and myArray is set to Null for size 0 and to new allocation for size > 0
 */
template<class Item>
Vec<Item>::Vec(unsigned size) {
	myArray = NULL;
	if(size > 0) {
		mySize = size;
		myArray = new Item[size]();
	} else if (size == 0) {
		mySize = 0;
		myArray = NULL;
	} else {
		throw range_error("Cannot set Vec<Item>tor to negative size");
	}
}

/* Set Values to Given Vec<Item>
 * @param: const reference Vec<Item>tor
 * Postcondition: Values match that of original
 */
template<class Item>
void Vec<Item>::makeCopyOf(const Vec<Item>& original) {
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

/* Vec<Item> Copy Constructor
 * @param: Reference to original Vec<Item>
 * Postcondition: Vec<Item> constructed has exact same values for size and elements of array
 */
template<class Item>
Vec<Item>::Vec(const Vec<Item>& original) {
	makeCopyOf(original);
}

/* Assignment Operator
 * @param: Reference to original Vec<Item> to be copied from
 * Return: Returns Vec<Item> that has exact same values for size and elements of array of original
 */
template<class Item>
Vec<Item>& Vec<Item>::operator=(const Vec<Item>& original) {

	if (this != &original) {
        delete [] myArray;
		myArray = NULL;
        makeCopyOf(original);

	}

	return *this;
}

/* Set Item Method
 * @param: index which must be within bounds of array range, and reference to Item
 * Precondition: Vec<Item> must have mySize greater than 0
 * Postcondition: Element with given index in array is assigned given Item
 */
template<class Item>
void Vec<Item>::setItem(unsigned index, const Item& it) {
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
 * Precondition: Vec<Item> must have mySize greater than 0
 * Return: Element with given index in array is assigned given Item
 */
template<class Item>
Item Vec<Item>::getItem(unsigned index) const {
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
template<class Item>
void Vec<Item>::setSize(unsigned newSize) {
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
 * Return: true if values of both Vec<Item>'s arrays are equal and size is equal
 */
template<class Item>
bool Vec<Item>::operator==(const Vec<Item>& v2) const {
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

/* Stream Output
 * Author: Joe Joel
 * @param: a file name, a string
 * Return: void
 */
template<class Item>
void Vec<Item>::writeTo(ostream& out) const {
	for (unsigned int i = 0; i < mySize; i++){
		out << myArray[i] <<endl;
	}
}

/* Read From Istream
 * @param: istream reference
 * Postcondition: Vec<Item> is populated with data from istream
 */
template<class Item>
void Vec<Item>::readFrom(istream& in) {
	for (unsigned i = 0; i < mySize; ++i) {
		in >> myArray[i];
	}
}

/* Returns reference to Item, allowing for assignment
 * Returns: reference to myArray[index] if valid, otherwise throw exception
 */
template<class Item>
Item& Vec<Item>::operator[](unsigned index) {
	if (mySize == 0) {
		throw range_error("Cannot index empty Vec<Item>...");
	} else if (index > (mySize-1)) {
		throw range_error("Index is out of bounds...");
	} else {
		return myArray[index];
	}
}

/* The subscript operator that retrieves a value
 * @param: an index, an unsigned
 * Author: Joe Joel
 * Return: an item stored at the index of a Vec<Item>
 */
template<class Item>
const Item& Vec<Item>::operator[](const unsigned index) const{
	if (index >= mySize) {
		throw range_error("Please enter a valid index between 0 and the size of the array.");
	} else {
		return myArray[index];
	}
}

/* Return Inequality
 * Returns: opposite of equality operator, see equality operator
 */
template<class Item>
bool Vec<Item>::operator!=(const Vec<Item>& original) const {
	return not (original == *this);
}

/* Read From
 * @params: filenameVec const operator+(const Vec<Item>& Vec<Item>1, const Vec<Item>& Vec<Item>2);
 * Precondition: file exists
 * Postcondition: Vec<Item> contains elements described in file.
 */
template<class Item>
void Vec<Item>::readFrom(const string fileName) {
    ifstream fin(fileName.c_str());
    assert(fin.is_open());

    Item inputItem;
    string inputString;

    getline(fin, inputString);
    setSize(atof(inputString.c_str()));

    for(unsigned i = 0; i < mySize; ++i) {
        fin >> inputString;
        inputItem = atof(inputString.c_str());
        setItem(i, inputItem);
    }

    fin.close();
}

/* File Output
 * Author: Joe Joel
 * @param: a file name, a string
 * Return: void
 */
template<class Item>
void Vec<Item>::writeTo(const string fileName){
	ofstream fout(fileName.c_str());
	assert(fout.is_open());
	fout << mySize << endl;
	for (unsigned i = 0; i < mySize; ++i) {
		fout << myArray[i] << endl;

	}
	fout.close();
}

/* Addition Overloading
 * @params: other Vec<Item>tor
 * Precondition: Both are of same size
 * Returns: returns Vec<Item>tor sum
 */
template<class Item>
Vec<Item> Vec<Item>::operator+(const Vec<Item>& other) const {
    if (mySize == other.getSize()) {
        Vec<Item> sumVector(mySize);
        for (unsigned i = 0; i < mySize; ++i) {
            sumVector[i] = myArray[i] + other[i];
        }
        return sumVector;
    } else {
        throw invalid_argument("Vectors should be same size...");
    }

};

/* The subtraction operator
 * Author: Joe Joel
 * @param: a variable name, a Vec<Item>
 * Return: a Vec<Item> of the sums of v1 and v2 in each element
 */
template<class Item>
Vec<Item> Vec<Item>::operator-(const Vec<Item>& v2) {
	if (v2.getSize() != mySize) {
		throw invalid_argument("Please subtract arrays of the same size.");
	} else {
		Vec newArr(mySize);
		for (unsigned i = 0; i < v2.getSize(); ++i) {
			newArr[i] = (myArray[i] - v2[i]);
		}
		return newArr;
	}
}

/* The dot product operator
 * Author: Joe Joel
 * @param: a variable name, a Vec<Item>
 * Return: a double of the sums of the product of each element
 */
template<class Item>
double Vec<Item>::operator*(const Vec<Item>& v2) {
	if (v2.getSize() != mySize) {
		throw invalid_argument("Please multiply arrays of the same size.");
	} else {
		double product = 0;
		for (unsigned i = 0; i < v2.getSize(); ++i) {
			product = product + (myArray[i] * v2[i]);
		}
		return product;
	}
}

/* Vec<Item> Destructor
 * @param: none
 * Postcondition: Vec<Item> myArray is deallocated and is set to Null, mySize set to 0
 */
template<class Item>
Vec<Item>::~Vec() {
	delete [] myArray;
	myArray = NULL;
	mySize = 0;
}


#endif /*VEC_H_*/
