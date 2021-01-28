#include "Node.h"
using namespace std;

Node::Node(KeyType key, DataType freq, Node *newLeft, Node *newRight) 
    : key(key), frequency(freq), left(nullptr), right(nullptr)
{
    if (newLeft)
	   left = new Node(*newLeft);

    if (newRight)
	   right = new Node(*newRight);
}

Node::Node(const Node& other) : left(nullptr), right(nullptr)
{
    *this = other;
}

//DESTRUCTOR
Node::~Node()
{
    if (left != nullptr)
	   delete left;
    if (right != nullptr)
	   delete right;
}

//----------------------------- TRAVERSING A BINARY TREE AND PRINT NODES METHODS ----------------------------//

void Node::inorder() const
{
    if (left != nullptr)
	   left->inorder();
    printItem();
    if (right != nullptr)
	   right->inorder();
}

void Node::preorder() const
{
    printItem();
    if (left != nullptr)
	   left->preorder();
    if (right != nullptr)
	   right->preorder();
}

void Node::postorder() const
{
    if (left != nullptr)
	   left->postorder();
    if (right != nullptr)
	   right->postorder();
    printItem();
}

//------------------------------------------------- GENERAL -------------------------------------------------//

void Node::printItem() const { cout << key << "," << frequency << " "; }

//OPERATOR= 
const Node& Node::operator=(const Node& other)
{
    if (this != &other)
    {
	   key = other.key;
	   frequency = other.frequency;

	   //left child handling
	   if (other.left)
		  left = (left == nullptr) ? new Node(*other.left) : other.left;
	   else
	   {
		  if (left)
			 delete left;
		  this->left = nullptr;
	   }

	   //right child handling
	   if (other.right)
		  right = (right == nullptr) ? new Node(*other.right) : other.right;
	   else
	   {
		  if (right)
			 delete right;
		  this->right = nullptr;
	   }
    }
    return *this;
}

//GETTERS
Node*    Node::getLeft() const		{ return left; }
Node*    Node::getRight() const		{ return right; }
KeyType  Node::getKey() const		{ return key; }
DataType Node::getFrequency() const	{ return frequency; }

//SETTERS
void Node::setKey(KeyType ch)		{ key = ch; }
void Node::setFrequency(DataType f) { frequency = f; }
void Node::setLeft(Node* const left)	{ if (this != nullptr) this->left = left; }
void Node::setRight(Node* const right)	{ if (this != nullptr) this->right = right; }