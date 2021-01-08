#ifndef __BSTREE_H
#define __BSTREE_H
#include <iostream>
#include "Node.h"

class BSTree
{
private:
    //PRIVATE CLASS MEMBERS
    Node* root;
public:
    BSTree();
    ~BSTree();
    BSTree(const BSTree& other) = delete;
    const BSTree& operator=(const BSTree& other) = delete;

    //PUBLIC STATIC CLASS MEMBER
    static int numOfNodes;

    //GENERAL BINARY-SEARCH TREE METHODS
    void makeEmpty();
    bool isEmpty() const;
    Node* getRoot() const;
    
    //2 OPTIONS FOR FIND FUNCTION
    Node* Find(const Item& theItem);
    Node* Find(KeyType theKey);

    //2 OPTIONS FOR INSERT FUNCTION
    void Insert(const Item& theItem);
    void Insert(KeyType ItemKey);
    
    //2 OPTIONS FOR DELETE FUNCTION
    void Delete(const Item& theItem);
    void Delete(KeyType ItemKey);

    //GENERAL METHODS
    void swapNodes(Node& first, Node& second);
};
#endif // !__BSTREE_H