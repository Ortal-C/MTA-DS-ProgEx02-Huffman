#include "Node.h"
using namespace std;

//CONSTRUCTORS
Node::Node() : item(nullptr), left(nullptr), right(nullptr) {}

Node::Node(Item theItem, Node *left, Node *right)
{
    this->item = new Item(theItem);
    if (left && !this->left)
	   this->left = new Node(*left);
    if (right && !this->right)
	   this->right = new Node(*right);
}

Node::Node(const Node& other) : item(nullptr), left(nullptr), right(nullptr)
{
    *this = other;
}

//DESTRUCTOR
Node::~Node()
{
    if (this)
    {
	   if (left)
		  delete left;
	   this->left = nullptr;
	   if (right)
		  delete right;
	   this->right = nullptr;
	   if (item)
		  delete item;
	   this->item = nullptr;
    }
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

void Node::printItem() const { cout << item->key << "," << item->frequency << " "; }

//OPERATOR= 
const Node& Node::operator=(const Node& other)
{
    if (this != &other)
    {
	   this->item = (item) ? other.item : new Item(*other.item);

	   //left child handling
	   if (other.left)
		  this->left = (left) ? other.left : new Node(*other.left);
	   else
	   {
		  if (left)
			 delete left;
		  this->left = nullptr;
	   }

	   //right child handling
	   if (other.right)
		  this->right = (right) ? other.right : new Node(*other.right);
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
Item*    Node::getItem() const		{ return item; }
KeyType  Node::getItemKey() const		{ return item->key; }
DataType Node::getItemFrequency() const	{ return item->frequency; }

//SETTERS
void Node::setItem(Item* const item)	{ this->item = (this->item) ? item : new Item(*item); }
void Node::setItemKey(KeyType ch)		{ this->item->key = ch; }
void Node::setItemFrequency(DataType f) { this->item->frequency = f; }
void Node::setLeft(Node* const left)	{ if (this != nullptr) this->left = left; }
void Node::setRight(Node* const right)	{ if (this != nullptr) this->right = right; }