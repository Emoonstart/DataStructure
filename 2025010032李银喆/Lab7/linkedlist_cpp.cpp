#include <iostream>
#include <cstdlib>

using namespace std;

// Node structure for linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(NULL) {}
};

// LinkedList class with head sentinel
class LinkedList {
private:
    Node* head;  // 哨兵节点，不存储有效数据
    int size;    // 有效节点个数
    
public:
    // Constructor: create empty list with sentinel
    LinkedList() {
        head = new Node(0);
        head->next = NULL;
        size = 0;
    }
    
    // Destructor: free all nodes
    ~LinkedList() {
        Node* current = head;
        while (current != NULL) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    LinkedList(const LinkedList& other) {
        head = new Node(0);
        head->next = NULL;
        size = 0;
        
        Node* current = other.head->next;
        Node* tail = head;
        while (current != NULL) {
            tail->next = new Node(current->data);
            tail = tail->next;
            size++;
            current = current->next;
        }
    }
    
    // Copy assignment operator
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            // Free existing nodes
            Node* current = head->next;
            while (current != NULL) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            delete head;
            
            // Copy from other
            head = new Node(0);
            head->next = NULL;
            size = 0;
            
            Node* currentOther = other.head->next;
            Node* tail = head;
            while (currentOther != NULL) {
                tail->next = new Node(currentOther->data);
                tail = tail->next;
                size++;
                currentOther = currentOther->next;
            }
        }
        return *this;
    }
    
    // Get size
    int getSize() const {
        return size;
    }
    
    // Check if empty
    bool isEmpty() const {
        return size == 0;
    }
    
    // Insert at head
    void insertHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head->next;
        head->next = newNode;
        size++;
    }
    
    // Remove from head
    bool removeHead(int& val) {
        if (isEmpty()) return false;
        
        Node* toDelete = head->next;
        val = toDelete->data;
        head->next = toDelete->next;
        delete toDelete;
        size--;
        return true;
    }
    
    // Print list
    void printList() const {
        Node* current = head->next;
        while (current != NULL) {
            cout << current->data;
            if (current->next != NULL) cout << " -> ";
            current = current->next;
        }
        cout << "[size=" << size << "]" << endl;
    }
};

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
    
    cout << "After destroy: destructor automatically called" << endl;
    
    return 0;
}