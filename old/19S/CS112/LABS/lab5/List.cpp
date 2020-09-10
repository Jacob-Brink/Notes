/* List.cpp contains definitions for List class
 * Lab5
 * Student: Jacob Brink
 * Date: 3/5/2019
 */

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

/* Default Constructor
 * Postcondition: Sets mySize to 0, and myFirst, myLast to NULL
 */
List::List() {
    mySize = 0;
    myFirst = myLast = NULL;
}

/* Destructor
 * Postcondition: All nodes are deleted, pointers set to NULL, mySize to 0
 */
List::~List() {
    delete myFirst;
    myFirst = myLast = NULL;
    mySize = 0;
}

/* Copy Constructor
 * Postcondition: Contents are cleared
 */
List::List(const List& original) {
	myFirst = myLast = NULL;
    mySize = 0;
    Node* oPtr = original.myFirst;
    while (oPtr != NULL) {
        append(oPtr->myItem);
        oPtr = oPtr->myNext;
    }
}

/* Assignment Operator
 * @params: original list
 * Postcondition: List contains elements of original
 */
List& List::operator=(const List& original) {
    //If two lists are different
    if (original.myFirst != myFirst) {
        //Destruct list
        this->~List();

        //copy values, setting myFirst and myLast automatically
        Node* oPtr = original.myFirst;
        while (oPtr != NULL) {
            append(oPtr->myItem);
            oPtr = oPtr->myNext;
        }
    }

    //set size to original size
    mySize = original.mySize;

    return *this;
}

/* Node Constructor
 * Postcondition: Sets myNext to NULL, myItem to default item
 */
List::Node::Node() {
    myItem = Item();
    myNext = NULL;
}

/* Node Destructor
 * Postcondition: pointer is deallocated (which automatically calls myNext destructor), then set to NULL; If myNext is not NULL, all nodes after will be destructed
 */
List::Node::~Node() {
    delete myNext;
    myNext = NULL;
    //cout << "~Node() deallocating the node containing item" << myItem << endl;
}

/* Explicit Node Constructor
 * @params: Item, nextPtr
 * Postcondition: Node contains Item and nextPtr
 */
List::Node::Node(const Item& it, Node* next) {
    myItem = it;
    myNext = next;
}

/* getSize
 * @params: none
 * Returns: mySize 
 */
unsigned List::getSize() const {
    return mySize;
}

/* getFirst
 * @params: none
 * Returns: First item if non empty, underflow_error if empty
 */
Item List::getFirst() const {
    if ((mySize == 0) || (myFirst == NULL)) {
        throw underflow_error("Cannot retreive first element from empty list...");
    }
    return myFirst->myItem;
}

/* getLast
 * @params: none
 * Returns: last item if size is not empty, underflow_error if empty
 */
Item List::getLast() const {
    if ((mySize == 0) || (myFirst == NULL)) {
        throw underflow_error("Cannot retreive first element from empty list...");
    }
    return myLast->myItem;
}

/* Append Element
 * @params: const ref Item
 * Precondition: none
 * Postcondition: new Node created with given Item, myLast points to new node, last node points or myFirst points to Node whether nonempty
 */
void List::append(const Item& it) {
    //Make new node
    Node* NodePtr = new Node(it, NULL);

    //if size is zero, set first pointer to newLastNode
    if ((mySize == 0) || (myFirst == NULL)) {
        myFirst = NodePtr;
    } else {
        //Set last node to point to new last node
        myLast->myNext = NodePtr;
    }
    //set myLast to point to last pointer
    myLast = NodePtr;
    mySize += 1;
}

