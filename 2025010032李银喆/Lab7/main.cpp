#include <iostream>
#include "list.h"

using namespace std;

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

    // 测试拷贝构造
    LinkedList list2 = list;
    list2.insertHead(99);
    cout << "Copy constructor: ";
    cout << "list: ";  list.printList();
    cout << "list2: "; list2.printList();

    // 测试拷贝赋值
    LinkedList list3;
    list3 = list;
    cout << "Copy assignment: ";
    cout << "list3: "; list3.printList();

    return 0;
}