#include "BinaryTree.h"

//CONSTRUCTORS
BTree::BTree() : root(nullptr) {}

//DESTRUCTOR
BTree::~BTree()
{
    if (root)
	   delete root;
    root = nullptr;
}

//--------------------------------------GENERAL BINARY-TREE METHODS------------------------------------------//

bool BTree::isEmpty() const				   { return root == nullptr; }
void BTree::makeEmpty()					   { delete root; }
Node* BTree::getRoot() const				   { return root; }