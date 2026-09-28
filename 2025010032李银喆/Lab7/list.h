#ifndef LIST_H
#define LIST_H

#include "listNode.h"

/* LinkedList 类：带头哨兵的单链表 */
class LinkedList {
private:
    listNode* head;   // 哨兵节点，data 不使用
    int size;         // 有效结点个数，不含哨兵

public:
    /* 构造函数：立哨兵 */
    LinkedList();

    /* 析构函数：释放所有结点 */
    ~LinkedList();

    /* 拷贝构造函数：深拷贝 */
    LinkedList(const LinkedList& other);

    /* 拷贝赋值运算符：先释放旧内存，再深拷贝 */
    LinkedList& operator=(const LinkedList& other);

    /* 返回链表大小 */
    int getSize() const;

    /* 判断是否为空表 */
    bool isEmpty() const;

    /* 表头插入 */
    void insertHead(int val);

    /* 表头删除，被删的值写入 val */
    bool removeHead(int& val);

    /* 遍历输出 */
    void printList() const;
};

#endif