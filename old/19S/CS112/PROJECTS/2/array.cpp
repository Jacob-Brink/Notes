/* array.cpp defines "C style" array operations
 * Name: Jacob Brink
 * Date: 2/12/19
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "array.h"
#include <fstream>

/* Initialize given array to be natural numbers
 * @param: double pointer array and size of given array
 * Postcondition: Array has elements that are natural numbers
 */

void initialize(double *a, unsigned size) {
	int val = 0;
	for (unsigned i = 0; i < size; i++) {
		val = i+1;
		a[i] = val;
	}
}
/* Prints to console elements of array
 * @param: double pointer array and size of given array
 * Postcondition: Elements are printed to screen
 */

void print(double *a, unsigned size) {
	for (unsigned i = 0; i < size; i++) {
		cout << *a << '\t';
		a++;
	}
}

/* Returns average value of elements in given array
 * @param: double pointer array and the size of the array
 * Postcondition: returns average value
 */

double average(double *a, unsigned size) {
	return sum(a, size)/size;
}

/* Returns sum of double values in given array
 * @param: double pointer array and the size of the array
 * Postcondition: returns sum of elements in array
 */

double sum(double *A, unsigned size) {
	double sum = 0.0;
	for (unsigned i = 0; i < size; ++i) {
		sum += *A;
		++A;
	}
	return sum;
}

/* Read values from stream into Array
 * @param: reference to istream, pointer, and size of values to be read from stream
 * Postcondition: pointer a points to array with values from stream
 */

void read(istream& in, double *a, unsigned size) {
	for (unsigned i = 0; i < size; ++i) {
		in >> a[i];
	}
}

/* Fills given array with numbers in file
 * @param: Reference to filename, reference to pointer array, and reference to numValues
 * Precondition: the fileName given must name a file whose first line is the number of the following lines of numbers in thefile.
 * Postcondition: Given pointer array is filled with numbers in file
 */

void fill(const string& fileName, double *&a, int &numValues) {
	//open file
	/*ifstream fin( fileName );
	assert( fin.is_open() );

	//create string for read input
	string sValue;

	//read numValues
	fin >> numValues;

	//deallocate memory in a, since we will overwrite all of it
	delete [] a;

	//assign a to new allocation of memory
	a = new double[numValues];


	for (unsigned i = 0; i < numValues; ++i) {
		if(!fin) { break; };
		fin >> a[i];
	}
	fin.close();*/
}

/* Array Resize
 * @param: reference of array pointer, unsigned oldSize, and unsigned newSize
 * Precondition: the oldSize is the size of the given pointer array
 * Postcondition: the given array pointer has the new size, and the old array is deallocated
 */

void resize(double *&a, unsigned oldSize, unsigned newSize) {
	double *newArray = new double[newSize];

	if (newSize < oldSize) {
		for(unsigned i = 0; i < newSize; ++i) {
			newArray[i] = a[i];
		}


	} else {
		for (unsigned i = 0; i < oldSize; ++i) {
			newArray[i] = a[i];
		}
		for (unsigned i = oldSize; i < newSize; ++i) {
			newArray[i] = 0;
		}

	}

	delete [] a;
	a = newArray;



}

/* Array Concatenation
 * @param: three pointer arrays and three respective sizes of arrays
 * Precondition: Respective sizes for to be combined arrays must be the actual sizes of the array
 * Postcondition: a3 is the combination of a1 and a2, and the size3 is the sum of the size1 and size2
 */

void concat(double *a1, unsigned size1, double *a2, unsigned size2, double *&a3, unsigned &size3){
    delete [] a3;
    a3 = NULL;
    size3 = size1 + size2;
    a3 = new double [size3];

    for (unsigned i=0; i < size1; ++i) {
        a3[i] = a1[i];
    }
    for (unsigned i = 0; i < size3; ++i) {
        a3[i+size1] = a2[i];
    }
}
