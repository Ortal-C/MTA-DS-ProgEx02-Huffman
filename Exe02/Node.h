#ifndef __NODE_H
#define __NODE_H
#include <iostream>
#include "Item.h"
using namespace std;

//General Tree-Node class
class Node
{
private:
    //PRIVATE CLASS MEMBERS
    Item* item;
    Node* left;
    Node* right;
public:
    Node();
    Node(Item item, Node* left = nullptr, Node* right = nullptr);
    Node(const Node& other);
    ~Node();

    //GENERAL
    void printItem() const;
    const Node& operator=(const Node& other);
    	  
    //TRAVERSING A BINARY TREE AND PRINT IT
    void inorder() const;
    void preorder() const;
    void postorder() const;

    //GETTERS
    Node* getLeft() const;
    Node* getRight() const;
    Item* getItem() const;
    KeyType getItemKey() const;
    DataType getItemFrequency() const;

    //SETTERS
    void setItem(Item* const item);
    void setItemKey(KeyType ch);
    void setItemFrequency(DataType freq);
    void setLeft(Node* const left);
    void setRight(Node* const right);
};
#endif //! __NODE_H