/*
* Engr220L - Lab 7 Prelab
* Date: <TODO>
* Author: <TODO>
*
* This file defines the factorial function 
* previously declared in main.c.  It recursively 
* calculates the factorial of the received input value.
* 
*/

int factorial(int n)
{
    if (n > 1)
		return n * factorial(n-1);
	return 1;
}