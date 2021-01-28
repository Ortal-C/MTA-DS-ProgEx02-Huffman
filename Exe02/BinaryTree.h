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
    BTree(Node* root);
    ~BTree();
    BTree(const BTree& other) = delete;
    const BTree& operator=(const BTree& other) = delete;

    //GENERAL
    void makeEmpty();
    bool isEmpty() const;

    //GETTER + SETTER TO ROOT
    Node* getRoot() const;
    void setRoot(Node* const root);
};
#endif // !__BINARYTREE_H