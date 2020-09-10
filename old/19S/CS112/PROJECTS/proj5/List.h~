/* List.h contains prototypes for List class
 * Proj5
 * Student: Jacob Brink
 * Date: 3/11/2019
 */

#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

template<class Item>
class List
{
    public:
        List();
        List(const List<Item>& original);
        List<Item>& operator=(const List<Item>& original);
        ~List();
        unsigned getSize() const;
        Item getFirst() const;
        Item getLast() const;
        int getIndexOf(const Item& it) const;

        void append(const Item& it);
        void prepend(const Item& it);
        void insert(const Item& it, int index);
        Item remove(int index);

        bool operator==(const List<Item>& original) const;
        bool operator!=(const List<Item>& original) const;

        void readFrom(istream& in);
        void writeTo(ostream& out, const string& separator) const;
        void readFrom(const string& filename);
        void writeTo(const string& filename, const string& separator) const;

    private:
        struct Node {
            Node();
            ~Node();
            Node(const Item& it, Node* next);
            Item myItem;
            Node* myNext;
        };

        unsigned mySize;
        Node* myFirst;
        Node* myLast;

        friend class ListTester;

};

#endif // LIST_H

/* Default Constructor
 * Postcondition: Sets mySize to 0, and myFirst, myLast to NULL
 */
template<class Item>
List<Item>::List() {
    mySize = 0;
    myFirst = myLast = NULL;
}

/* Destructor
 * Postcondition: All nodes are deleted, pointers set to NULL, mySize to 0
 */
template<class Item>
List<Item>::~List() {
    delete myFirst;
    myFirst = myLast = NULL;
    mySize = 0;
}

/* Copy Constructor
 * Postcondition: Contents are cleared
 */
template<class Item>
List<Item>::List(const List<Item>& original) {
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
 * Postcondition: List<Item> contains elements of original
 */
template<class Item>
List<Item>& List<Item>::operator=(const List<Item>& original) {
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
template<class Item>
List<Item>::Node::Node() {
    myItem = Item();
    myNext = NULL;
}

/* Node Destructor
 * Postcondition: pointer is deallocated (which automatically calls myNext destructor), then set to NULL; If myNext is not NULL, all nodes after will be destructed
 */
template<class Item>
List<Item>::Node::~Node() {
    delete myNext;
    myNext = NULL;
    //cout << "~Node() deallocating the node containing item" << myItem << endl;
}

/* Explicit Node Constructor
 * @params: Item, nextPtr
 * Postcondition: Node contains Item and nextPtr
 */
template<class Item>
List<Item>::Node::Node(const Item& it, Node* next) {
    myItem = it;
    myNext = next;
}

/* getSize
 * @params: none
 * Returns: mySize
 */
template<class Item>
unsigned List<Item>::getSize() const {
    return mySize;
}

/* getFirst
 * @params: none
 * Returns: First item if non empty, underflow_error if empty
 */
template<class Item>
Item List<Item>::getFirst() const {
    if ((mySize == 0) || (myFirst == NULL)) {
        throw underflow_error("Cannot retreive first element from empty list...");
    }
    return myFirst->myItem;
}

/* getLast
 * @params: none
 * Returns: last item if size is not empty, underflow_error if empty
 */
template<class Item>
Item List<Item>::getLast() const {
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
template<class Item>
void List<Item>::append(const Item& it) {
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

/* Equality Overloading
 * @params: Original List
 * Precondition: none
 * Postcondition: none
 * Returns: True if lists are same size and have same content, otherwise false
 */
template<class Item>
bool List<Item>::operator==(const List<Item>& original) const {
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

/* Inequality
 * @params: Original List
 * Precondition: none
 * Postcondition: none
 * Returns: true if not equal, false if equal
 */
template<class Item>
bool List<Item>::operator!=(const List<Item>& original) const {
    return not (*this==original);
}

/* readFrom stream
 * @params: reference to istream
 * Precondition: none
 * Postcondition: list contains elements in istream up until newline
 */
template<class Item>
void List<Item>::readFrom(istream& in) {
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

/* writeTo stream
 * @params: ostream, string separator
 * Precondition: none
 * Postcondition: ostream contains values from list separated by the separator
 */
template<class Item>
void List<Item>::writeTo(ostream& out, const string& separator) const {
    Node* oPtr = myFirst;
    while (oPtr != NULL) {
        out << separator << oPtr->myItem;
        oPtr = oPtr->myNext;
    }
}

/* readFrom file
 * @params: filename string
 * Precondition: file exists
 * Postcondition: list contains elements from file up until newline
 */
template<class Item>
void List<Item>::readFrom(const string& filename) {
    delete myFirst;
    mySize = 0;
    ifstream fin(filename.c_str());
    assert( fin.is_open() );

    string input;

    while (fin >> input) {
        append(atoi(input.c_str()));
    }
}

/* writeTo file
 * @params: filename string, separator string
 * Precondition: file exists
 * Postcondition: file contains values of list
 */
template<class Item>
void List<Item>::writeTo(const string& filename, const string& separator) const {
    ofstream fout(filename.c_str());
    assert( fout.is_open() );
    writeTo(fout, separator);
}

/* prepend
 * @params: Item
 * Precondition: none
 * Postcondition: list contains given item at index 0
 */
template<class Item>
void List<Item>::prepend(const Item& it) {
    Node* nodePtr = new Node(it, myFirst);
    myFirst = nodePtr;
    if (mySize == 0) {
        myLast = nodePtr;
    }
    mySize += 1;
}

/* getIndexOf
 * @params: Item
 * Returns: Index of first appearance of given Item, or -1 if Item not found
 */
template<class Item>
int List<Item>::getIndexOf(const Item& it) const {
    unsigned counter = 0;
    for (Node* nPtr = myFirst; nPtr != NULL; nPtr = nPtr->myNext) {
        if (nPtr->myItem == it) {
            return counter;
        }
        ++counter;
    }
    return -1;
}

/* insert item
 * @params: Item, index
 * Precondition: none
 * Postcondition: Item is placed at index if index is within range, otherwise it is appended or prepended whether the index is below or above range
 */
template<class Item>
void List<Item>::insert(const Item& it, int index) {
    //convert unsigned to integer index
    int indexSize = mySize - 1;

    if (index > indexSize) {
        append(it);
    } else if (index <= 0) {
        prepend(it);
    } else {
        Node* nPtr = myFirst;
        //crawl through chain until pointer is sitting at node at index - 1
        for (int i = 0; i < (index-1); ++i) {
            nPtr = nPtr->myNext;
        }
        //create new node with pointer pointing to node next after the one at index - 1
        Node *newNodePtr = new Node(it, nPtr->myNext);
        nPtr->myNext = newNodePtr;

        mySize += 1;
    }
}

/* remove item
 * @params: index
 * Precondition: list is non empty
 * Postcondition: if index is in range, deletes node; if not in range, removes either first or last node if index is less than or greater than the range; if empty, throws error
 * Returns: returns Item that was deleted, error if size == 0
 */
template<class Item>
Item List<Item>::remove(int index) {
    int mySizeInt = mySize;
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
        } else if (index >= (mySizeInt-1)) {
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
            for (int i = 0; i < (index-1); ++i) {
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
		//Delete called on empty list calls error
        throw underflow_error("Cannot delete element on empty list...");

    }

}
