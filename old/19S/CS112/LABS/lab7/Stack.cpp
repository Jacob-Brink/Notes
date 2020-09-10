/* Stack.cpp defines the dynamically allocated (array-based ) Stack operations.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 */

#include "Stack.h"
#include <stdexcept> // overflow_error, underflow_error


/* isFull getter
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: true if mySize == myCapacity, else false
 */
bool Stack::isFull() const {
	return mySize == myCapacity;
}

/* top item getter
 * Parameter: none
 * Precondition: none
 * Postcondition: none
 * Returns: returns top item, unless mySize is zero in which an exception would be raised
 */
Item Stack::peekTop() const {
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
Item Stack::pop() {
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
void Stack::push(const Item& it) {
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
bool Stack::isEmpty() const {
	return mySize == 0;
}

/* explicit-value constructor
 * Parameter: capacity, an unsigned value.
 * Precondition: capacity > 0.
 * Postcondition: mySize == 0 && myCapacity == capacity
 *              && myArray contains the address of a dynamic array of 'capacity' entries.
 */
Stack::Stack(unsigned capacity) {
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
Stack::Stack(const Stack& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
void Stack::makeCopyOf(const Stack& original) {
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
Stack::~Stack() {
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
Stack& Stack::operator=(const Stack& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

