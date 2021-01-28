#include "BinaryTree.h"

//CONSTRUCTORS
BTree::BTree() : root(nullptr) {}

BTree::BTree(Node* root) : root(nullptr) { setRoot(root); }

//DESTRUCTOR
BTree::~BTree()
{
    if (root != nullptr)
	   delete root;
    root = nullptr;
}

//--------------------------------------GENERAL BINARY-TREE METHODS------------------------------------------//

bool BTree::isEmpty() const	  { return root == nullptr; }
void BTree::makeEmpty()		  { delete root; }
Node* BTree::getRoot() const	  { return root; }

void BTree::setRoot(Node* const root)
{
    this->root = (this != nullptr) ? root : new Node(*root);
}