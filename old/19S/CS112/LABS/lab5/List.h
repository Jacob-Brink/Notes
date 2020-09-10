/* List.h contains prototypes for List class
 * Lab5
 * Student: Jacob Brink
 * Date: 3/5/2019
 */

#ifndef LIST_H
#define LIST_H


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
        void append(const Item& it);

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
