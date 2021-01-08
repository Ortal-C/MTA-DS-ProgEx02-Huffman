#ifndef __BINARYTREE_H
#define __BINARYTREE_H
#include <iostream>
#include "Node.h"

//Static implementation for Binary-Tree
class BTree
{
private:
    //PRIVATE CLASS MEMBERS
    Node* root;

public:
    BTree();
    ~BTree();
    BTree(const BTree& other) = delete;
    const BTree& operator=(const BTree& other) = delete;

    //GENERAL
    void makeEmpty();
    bool isEmpty() const;
    Node* getRoot() const;
};
#endif // !__BINARYTREE_H