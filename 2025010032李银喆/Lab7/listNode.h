#ifndef LISTNODE_H
#define LISTNODE_H

// 结点结构（使用 0 而非 nullptr/NULL，兼容 old g++ 4.7.0）
struct ListNode {
    int data;
    struct ListNode* pred;
    struct ListNode* succ;

    ListNode() : data(0), pred(0), succ(0) {}
    ListNode(int val) : data(val), pred(0), succ(0) {}
};

#endif