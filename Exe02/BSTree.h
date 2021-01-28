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
    
    //DICTIONARY ADT METHODS
    Node* Find(KeyType theKey);
    void Insert(KeyType ItemKey);
    void Delete(KeyType ItemKey);

    //GENERAL METHODS
    void swapNodes(Node& first, Node& second);
    void convertBSTtoArray(Node* currNode, int& pos, Node**& resArr);
    void convertToArray(Node**& resArr);
};
#endif // !__BSTREE_H