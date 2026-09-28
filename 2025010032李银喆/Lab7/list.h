#ifndef LIST_H
#define LIST_H

// List 类（使用链表节点，实际实现在 main.cpp 中）
// 以兼容旧编译器 g++ 4.7.0
class List {
private:
    int _size;
    struct ListNode {
        int data;
        struct ListNode* pred;
        struct ListNode* succ;
        ListNode() : data(0), pred(NULL), succ(NULL) {}
        ListNode(int val) : data(val), pred(NULL), succ(NULL) {}
    };
    int _size;
    struct ListNode* m_header;
    struct ListNode* m_trailer;

protected:
    void init();
    void clear();

public:
    List();
    ~List();

    int size() const;
    bool empty() const;

    ListNode* header() const;
    ListNode* trailer() const;

    int remove(ListNode* p);

    int find(int e) const;

    void output() const;

    void insertAsSucc(int val);
};

#endif