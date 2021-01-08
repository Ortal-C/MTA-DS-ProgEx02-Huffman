#include "BSTree.h"

//initial of numOfNodes
int BSTree::numOfNodes = 0;

//-----------------------------------------------------------------------------------------------------------//

//CONSTRUCTOR
BSTree::BSTree() : root(nullptr) {}

//DESTRUCTOR
BSTree::~BSTree()
{
    delete root; //destructive recursively of all nodes in the tree
    root = nullptr;
}

//--------------------------------------- DICTIONARY ADT METHODS --------------------------------------------//

Node* BSTree::Find(const Item& theItem)
{
    return Find(theItem.getKey());
}

Node* BSTree::Find(KeyType theKey)
{
    char ch;
    Node* temp = root;
    while (temp)
    {
	   ch = temp->getItemKey();
	   if (theKey == ch)
		  return temp;
	   else if ((int)theKey > (int)ch) //if ASCII code of ch is smaller than theItem.key we'll go to left child
		  temp = temp->getLeft();
	   else
		  temp = temp->getRight();
    }
    return nullptr;
}

void BSTree::Insert(const Item& item)
{
    Insert(item.getKey());
}

void BSTree::Insert(KeyType ItemKey)
{
    Node* parent = nullptr;
    Node* curr = root;
    //Checking if there is a key in tree. if so we'll add 1 to its frequency
    while (curr)
    {
	   parent = curr;
	   char ch = curr->getItemKey();
	   if (ItemKey == ch)
	   {
		  curr->setItemFrequency(curr->getItemFrequency()+ 1);
		  return;
	   }
	   else if ((int)ItemKey < (int)ch)
		  curr = curr->getLeft();
	   else
		  curr = curr->getRight();
    }

    //If here => didn't find matching key in tree so we'll add one.
    Node* newNode = new Node(ItemKey);
    numOfNodes += 1;
    if (parent)
    {
	   char parentKey = parent->getItemKey();
	   if ((int)parentKey > (int)ItemKey)
		  parent->setLeft(newNode);
	   else
		  parent->setRight(newNode);
    }
    else
	   root = newNode;
}


void BSTree::Delete(const Item& theItem)
{
    Delete(theItem.getKey());
}

void BSTree::Delete(KeyType itemKey)
{
    Node* parent = nullptr;
    Node* curr = root;

    //Checking if item is already in tree. 
    while (curr)
    {
	   parent = curr;
	   char ch = curr->getItemKey();
	   if (itemKey == ch)
	   {
		  //If here - we found the node to delete.
		  if (curr->getLeft() && !curr->getRight())		//CASE 1: only have left child
			 parent->setLeft(curr->getLeft());
		  else if (!curr->getLeft() && curr->getRight())	//CASE 2: only have right child
			 parent->setRight(curr->getRight());
		  else if (curr->getLeft() && curr->getRight())	//CASE 3: curr has 2 children
		  {
			 //Find max in right-sub-tree
			 Node* tmp = curr;
			 while (tmp->getRight())
				tmp = tmp->getRight();

			 swapNodes(*tmp, *curr);
			 swapNodes(*curr, *(curr->getLeft()));
			 //curr now is in the left leaf in track so we can delete him.
		  }
		  delete curr;
		  numOfNodes -= 1;
	   }
	   else if ((int)itemKey > (int)ch)
		  curr = curr->getLeft();
	   else
		  curr = curr->getRight();
    }
}

//-------------------------------------------- GENERAL METHODS ----------------------------------------------//

void BSTree::makeEmpty()		  { delete root; }
bool BSTree::isEmpty() const	  { return (root == nullptr); }
Node* BSTree::getRoot() const	  { return root; }

void BSTree::swapNodes(Node& first, Node& second)
{
    Node tmp = first;
    first = second;
    second = tmp;
}
