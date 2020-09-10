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

bool List::operator==(const List& original) const {
    //check element equality only if same size
    if (mySize == original.mySize) {
        Node* oPtr = myFirst;
        Node* iPtr = original.myFirst;
        while((oPtr != NULL) || (iPtr != NULL)) {
            //if any value is different, return false
            if (oPtr->myItem != iPtr->myItem) {
                return false;
            }
            oPtr = oPtr->myNext;
            iPtr = iPtr->myNext;
        }
    } else {
        return false;
    }

    return true;
}

bool List::operator!=(const List& original) const {
    return not (*this==original);
}

void List::readFrom(istream& in) {
    delete myFirst;
    mySize = 0;

    string line, input;
    //gather one line
    getline(in, line);

    //create new stream limited to one line
    stringstream ss;
    ss << line;
    while (ss >> input) {
        append(atoi(input.c_str()));
    }

}

void List::writeTo(ostream& out, const string& separator) const {
    Node* oPtr = myFirst;
    while (oPtr != NULL) {
        out << separator << oPtr->myItem;
        oPtr = oPtr->myNext;
    }
}

void List::readFrom(const string& filename) {
    delete myFirst;
    mySize = 0;
    ifstream fin(filename.c_str());
    assert( fin.is_open() );

    string input;

    while (fin >> input) {
        append(atoi(input.c_str()));
    }
}

void List::writeTo(const string& filename, const string& separator) const {
    ofstream fout(filename.c_str());
    assert( fout.is_open() );

    writeTo(fout, separator);
}

void List::prepend(const Item& it) {
    Node* nodePtr = new Node(it, myFirst);
    myFirst = nodePtr;
    if (mySize == 0) {
        myLast = nodePtr;
    }
    mySize += 1;
}

int List::getIndexOf(const Item& it) const {
    unsigned counter = 0;
    for (Node* nPtr = myFirst; nPtr != NULL; nPtr = nPtr->myNext) {
        if (nPtr->myItem == it) {
            return counter;
        }
        ++counter;
    }
    return -1;
}

void List::insert(const Item& it, int index) {
    //convert unsigned to integer index
    int indexSize = mySize - 1;

    if (index > indexSize) {
        append(it);
    } else if (index <= 0) {
        prepend(it);
    } else {
        Node* nPtr = myFirst;
        //crawl through chain until pointer is sitting at node at index - 1
        for (unsigned i = 0; i < (index-1); ++i) {
            nPtr = nPtr->myNext;
        }
        //create new node with pointer pointing to node next after the one at index - 1
        Node *newNodePtr = new Node(it, nPtr->myNext);
        nPtr->myNext = newNodePtr;

        mySize += 1;
    }
}

Item List::remove(int index) {
    if (mySize != 0) {
        Item deletedElement;
        //Index is less than or equal to zero
        if (index <= 0) {
            //get new First Ptr from second element in list
            Node* newFirstPtr = myFirst->myNext;

            //retreive value for returning before deallocation
            deletedElement = myFirst->myItem;

            //deallocate node, but set myFirst-myNext to NULL so the whole list doesn't destruct
            myFirst->myNext = NULL;
            delete myFirst;

            //if size is one, set myLast to point to newFirst node
            if (mySize == 1) {
                myLast = newFirstPtr;
            }

            //update myFirst pointer to newFirstPtr
            myFirst = newFirstPtr;

        //Index is greater than size or last element index
        } else if (index >= (mySize-1)) {
            Node* oPtr = myFirst;
            while (oPtr->myNext != myLast) {
                oPtr = oPtr->myNext;
            }

            deletedElement = myLast->myItem;
            delete myLast;
            myLast = oPtr;
            myLast->myNext = NULL;

            if (mySize == 1) {
                myFirst = myLast;
            }

        } else {
            Node* nPtr = myFirst;
            //crawl through chain until pointer is sitting at node at index - 1
            for (unsigned i = 0; i < (index-1); ++i) {
                nPtr = nPtr->myNext;
            }
            //save a copy of the pointer to the element after the deleted element since deleting the node will lose its pointer to it
            Node* newNext = nPtr->myNext->myNext;

            //assign deletedElement
            deletedElement = nPtr->myNext->myItem;

            //deallocate the deleted element, but set it to null so the list doesn't blow up bruh
            nPtr->myNext = NULL;
            delete nPtr->myNext;

            //Set myNext of node before deleted element to pointer to node after element
            nPtr->myNext = newNext;
        }
        mySize -= 1;
        return deletedElement;
    } else {
        //throw error?

    }

}
