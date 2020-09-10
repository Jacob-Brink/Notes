/* List.cpp contains definitions for List class
 * Lab5
 * Student: Jacob Brink
 * Date: 3/5/2019
 */

#include "List.h"
#include<iostream>
#include <stdexcept>

using namespace std;

List::List() {
    mySize = 0;
    myFirst = myLast = NULL;
}

List::~List() {
    delete myFirst;
    myFirst = myLast = NULL;
    mySize = 0;
}

List::List(const List& original) {
    myFirst = myLast = NULL;
    mySize = 0;
    Node* oPtr = original.myFirst;
    while (oPtr != NULL) {
        append(oPtr->myItem);
        oPtr = oPtr->myNext;
    }
}

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



List::Node::Node() {
    myItem = Item();
    myNext = NULL;
}

List::Node::~Node() {
    delete myNext;
    myNext = NULL;
    //cout << "~Node() deallocating the node containing item" << myItem << endl;
}

List::Node::Node(const Item& it, Node* next) {
    myItem = it;
    myNext = next;
}

unsigned List::getSize() const {
    return mySize;
}

Item List::getFirst() const {
    if ((mySize == 0) || (myFirst == NULL)) {
        throw underflow_error("Cannot retreive first element from empty list...");
    }
    return myFirst->myItem;
}
Item List::getLast() const {
    if ((mySize == 0) || (myFirst == NULL)) {
        throw underflow_error("Cannot retreive first element from empty list...");
    }
    return myLast->myItem;
}

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


