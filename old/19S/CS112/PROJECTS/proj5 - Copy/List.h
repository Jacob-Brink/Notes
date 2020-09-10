/* List.h contains prototypes for List class
 * Lab5
 * Student: Jacob Brink
 * Date: 3/5/2019
 */

#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

typedef double Item;
class List
{
    public:
        List();
        List(const List& original);
        List& operator=(const List& original);
        ~List();
        unsigned getSize() const;
        Item getFirst() const;
        Item getLast() const;
        int getIndexOf(const Item& it) const;

        void append(const Item& it);
        void prepend(const Item& it);
        void insert(const Item& it, int index);
        Item remove(int index);

        bool operator==(const List& original) const;
        bool operator!=(const List& original) const;

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
