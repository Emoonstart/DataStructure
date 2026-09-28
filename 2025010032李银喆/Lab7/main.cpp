#include <iostream>
#include "list.h"

using namespace std;

/* Constructor: create sentinel node */
LinkedList::LinkedList() {
    head = new listNode(0);
    head->next = NULL;
    size = 0;
}

/* Destructor: free all nodes including sentinel */
LinkedList::~LinkedList() {
    listNode* current = head;
    while (current != NULL) {
        listNode* next = current->next;
        delete current;
        current = next;
    }
}

/* Copy constructor: deep copy */
LinkedList::LinkedList(const LinkedList& other) {
    head = new listNode(0);
    head->next = NULL;
    size = 0;

    listNode* cur = other.head->next;
    listNode* tail = head;
    while (cur != NULL) {
        tail->next = new listNode(cur->data);
        tail = tail->next;
        size++;
        cur = cur->next;
    }
}

/* Copy assignment: free old memory, then deep copy */
LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this != &other) {
        /* free old nodes */
        listNode* current = head->next;
        while (current != NULL) {
            listNode* next = current->next;
            delete current;
            current = next;
        }
        delete head;

        /* deep copy from other */
        head = new listNode(0);
        head->next = NULL;
        size = 0;

        listNode* cur = other.head->next;
        listNode* tail = head;
        while (cur != NULL) {
            tail->next = new listNode(cur->data);
            tail = tail->next;
            size++;
            cur = cur->next;
        }
    }
    return *this;
}

int LinkedList::getSize() const {
    return size;
}

bool LinkedList::isEmpty() const {
    return size == 0;
}

/* Insert at head */
void LinkedList::insertHead(int val) {
    listNode* newNode = new listNode(val);
    newNode->next = head->next;
    head->next = newNode;
    size++;
}

/* Remove from head */
bool LinkedList::removeHead(int& val) {
    if (isEmpty()) return false;

    listNode* toDelete = head->next;
    val = toDelete->data;
    head->next = toDelete->next;
    delete toDelete;
    size--;
    return true;
}

/* Print list: start from head->next, skip sentinel */
void LinkedList::printList() const {
    listNode* current = head->next;
    while (current != NULL) {
        cout << current->data;
        if (current->next != NULL) cout << " -> ";
        current = current->next;
    }
    cout << "[size=" << size << "]" << endl;
}

int main() {
    LinkedList list;

    cout << "After init: ";
    cout << "size=" << list.getSize() << ", empty=" << list.isEmpty() << endl;

    cout << "Insert 10 at head: ";
    list.insertHead(10);
    list.printList();

    cout << "Insert 20 at head: ";
    list.insertHead(20);
    list.printList();

    cout << "Remove from head: ";
    int removedVal;
    if (list.removeHead(removedVal)) {
        cout << "Removed: " << removedVal << endl;
    }
    list.printList();

    // Test copy constructor
    LinkedList list2 = list;
    list2.insertHead(99);
    cout << "Copy constructor: ";
    cout << "list: ";  list.printList();
    cout << "list2: "; list2.printList();

    // Test copy assignment
    LinkedList list3;
    list3 = list;
    cout << "Copy assignment: ";
    cout << "list3: "; list3.printList();

    return 0;
}