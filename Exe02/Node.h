#ifndef __NODE_H
#define __NODE_H
#include <iostream>
using namespace std;

typedef char KeyType;
typedef int  DataType;

//General Tree-Node class
class Node
{
private:
    //PRIVATE CLASS MEMBERS
    KeyType key;
    DataType frequency;
    Node *left, *right;
public:
    Node(KeyType k=EOF, DataType freq = 1, Node* left = nullptr, Node* right = nullptr);
    Node(const Node& other);
    const Node& operator=(const Node& other);
    ~Node();

    //GENERAL
    void printItem() const;

    //TRAVERSING A BINARY TREE (AND PRINT TREE)
    void inorder() const;
    void preorder() const;
    void postorder() const;

    //GETTERS
    Node* getLeft() const;
    Node* getRight() const;
    KeyType getKey() const;
    DataType getFrequency() const;

    //SETTERS
    void setKey(KeyType ch);
    void setFrequency(DataType freq);
    void setLeft(Node* const left);
    void setRight(Node* const right);

    //FRIEND
    friend class  BTree;
};
#endif //! __NODE_H