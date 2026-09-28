#ifndef LISTNODE_H
#define LISTNODE_H

#include <cstddef>

/* Node: data field + pointer field */
struct listNode {
    int data;
    listNode* next;

    listNode(int val) : data(val), next(NULL) {}
};

#endif