/* Stack.h provides a (dynamic-array-based) Stack class.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 * 
 * Invariant: mySize == 0 && isEmpty() && !isFull()
 *         || mySize == myCapacity && !isEmpty() && isFull()
 *         || mySize > 0 && mySize < myCapacity && !isEmpty() && !isFull().
 * Notes: 
 * 1. Member mySize always contains the index of the next empty space in myArray
 *        (the index of the array element into which the next pushed item will be placed).
 * 2. Sending push() to a full Stack throws the exception Stack::Overflow.
 * 3. Sending pop() or peekTop() to an empty Stack throws the exception Stack::Underflow.
 */

#ifndef STACK_H_
#define STACK_H_

/* Stack.cpp defines the dynamically allocated (array-based ) Stack operations.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 */

#include <stdexcept> // overflow_error, underflow_error
#include "StackException.h"
#include <string>
#include <iostream>
using namespace std;

template<class Item>
class Stack {
public:
	Stack(unsigned capacity);
	Stack(const Stack& original);
	bool isEmpty() const;
	bool isFull() const;
	unsigned getSize() const;
	unsigned getCapacity() const;
	
	Item peekTop() const;
	Item pop();
	
	void push(const Item& it);
	void setCapacity(unsigned newCapacity);
	
	~Stack();
	Stack& operator=(const Stack& original);
	
protected:
	void makeCopyOf(const Stack& original);
	
private:
	unsigned myCapacity;
	unsigned mySize;
	Item*    myArray;
	friend class StackTester;
};

/* size getter
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: mySize
 */
template<class Item>
unsigned Stack<Item>::getSize() const {
	return mySize;
}

/* capacity getter
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: myCapacity
 */
template<class Item>
unsigned Stack<Item>::getCapacity() const {
	return myCapacity;
}

/* set new capacity
 * Parameter: none
 * Precondition: new capacity must be greater than or equal to mySize
 * Postcondition: none
 * Returns: none
 */
template<class Item>
void Stack<Item>::setCapacity(unsigned newCapacity) {
	if ( newCapacity == 0 ) {
		throw StackException("setCapacity()", "given capacity is zero");
	}
	if ( newCapacity < mySize ) {
		throw StackException("setCapacity()", "given capacity is less than mySize");
	}

	Item* newArray = new Item[newCapacity];
	for (unsigned i = 0; i < mySize; ++i) {
		newArray[i] = myArray[i];
	}
	delete [] myArray;
	myArray = newArray;
	myCapacity = newCapacity;
	
}

/* isFull getter
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: true if mySize == myCapacity, else false
 */
template<class Item>
bool Stack<Item>::isFull() const {
	return mySize == myCapacity;
}

/* top item getter
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: returns top item, unless mySize is zero in which an exception would be raised
 */
template<class Item>
Item Stack<Item>::peekTop() const {
	if ( isEmpty() ) {
		throw StackException("peekTop()", "stack is empty");
	}
	return myArray[mySize - 1];
}

/* removes top of stack
 * Parameter: none
 * Precondition: none
 * Postcondition: mySize decreases by 1
 * Returns: returns top item
 */
template<class Item>
Item Stack<Item>::pop() {
	if ( isEmpty() ) {
		throw StackException("pop()", "stack is empty!");
	}
	return myArray[--mySize];
}

/* add item to top of stack
 * Parameter: const ref item
 * Precondition: none
 * Postcondition: mySize increases by 1, new item is top element
 * Returns: none
 */
template<class Item>
void Stack<Item>::push(const Item& it) {
	if ( isFull() ) {
		throw StackException("push()", "stack is full!");
	}
	myArray[mySize] = it;
	++mySize;
}

/* isEmpty getter
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: true if mySize > 0, else false
 */
template<class Item>
bool Stack<Item>::isEmpty() const {
	return mySize == 0;
}

/* explicit-value constructor
 * Parameter: capacity, an unsigned value.
 * Precondition: capacity > 0.
 * Postcondition: mySize == 0 && myCapacity == capacity
 *              && myArray contains the address of a dynamic array of 'capacity' entries.
 */
template<class Item>
Stack<Item>::Stack(unsigned capacity) {
   if (capacity < 1) {
	   throw StackException("Stack(capacity)", "capacity must be positive!");
   }
   mySize = 0;
   myCapacity = capacity;
   myArray = new Item[capacity];
}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template<class Item>
Stack<Item>::Stack(const Stack<Item>& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
template<class Item>
void Stack<Item>::makeCopyOf(const Stack<Item>& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	mySize = original.mySize;
}

/* destructor
 * Postcondition: myCapacity == 0 && mySize == 0
 *             && myArray has been deallocated.
 */
template<class Item>
Stack<Item>::~Stack() {
	delete [] myArray;
	myArray = NULL;
	myCapacity = 0;
	mySize = 0;
}

/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
template<class Item>
Stack<Item>& Stack<Item>::operator=(const Stack<Item>& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

#endif

