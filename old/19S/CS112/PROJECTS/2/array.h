/* array.h declares "C style" array operations.
 * Name: Jacob Brink
 * Date: 2/12/19
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include <iostream>
#include <cassert>
using namespace std;

void initialize(double *a, unsigned size);

void print(double *a, unsigned size);

double average(double *a, unsigned size);

double sum(double *A, unsigned size);

void read(istream& in, double *a, unsigned size);

void fill(const string& fileName, double *&a, unsigned &numValues);

void resize(double *&a, unsigned oldSize, unsigned newSize);

void concat(double *a1, unsigned size1, double *a2, unsigned size2, double *&a3, unsigned &size3);

