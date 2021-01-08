#include "MinPriorityQueue.h"

//-----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- PUBLIC METHODS -----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

//CONSTRUCTOR
MinPQ::MinPQ(const BSTree& BST) : heapSize(0), maxSize(BST.numOfNodes)
{
    data = new Node*[maxSize];
    convertBSTtoMinPQData(BST.getRoot());
    allocated = true;
}

//CONSTRUCTOR => known also as BuildHeap (Floyd's algorithm)
MinPQ::MinPQ(Node** staticTree, int n)
{
    heapSize = maxSize = n;
    data = staticTree;
    allocated = false;
    for (int i = n / 2 - 1; i >= 0; i--)
	   fixHeap(i);
}

//DESTRUCTOR
MinPQ::~MinPQ()
{
    if (allocated)
    {
	   for (int i = 0; i < maxSize; i++)
	   {
		  delete data[i];
		  data[i] = nullptr;
	   }
	   delete[] data;
    }
    data = nullptr;
}

//------------------------------------------------- GENERAL -------------------------------------------------//

void MinPQ::makeEmpty()
{
    for (int i = 0; i < heapSize; i++)
	   delete data[i];
    delete[] data;
}

bool MinPQ::isEmpty() const		 { return heapSize == 0; }

void MinPQ::heapSort(Node** data, int n)
{
    MinPQ Q(data, n);
    Node* item;
    for (int i = n - 1; i >= 1; i--)
    {
	   item = Q.deleteMin();
	   Q.data[i] = item;
    }
}

//GETTERS
int MinPQ::getHeapSize() const	 { return heapSize; }
int MinPQ::getMaxSize() const		 { return maxSize; }
bool MinPQ::isDataAllocated() const { return allocated; }


//------------------------------------------ PRIORITY-QUEUE METHODS -----------------------------------------//

//Function returns the minimal item in the heap
Node** MinPQ::min() const
{ 
    return &data[0];
}

//Function deletes and returns the minimal item in the heap and fix its order
Node* MinPQ::deleteMin()
{
    if (heapSize >= 1)
    {
	   Node* minNode = data[0];
	   heapSize--;
	   data[0] = data[heapSize];
	   fixHeap(0);
	   return minNode;
    }
    else
    {
	   cout << "ERROR ==> heap is empty." << endl;
	   exit(1);
    }
}
//Function inserts node into the heap and fix its order
void MinPQ::insertMin(Node* node)
{
    if (heapSize <= maxSize)
    {
	   int i = heapSize;
	   heapSize++;
	   DataType nodeData = node->getItemFrequency();
	   while (i > 0 && (data[parentPos(i)]->getItemFrequency() > nodeData))
	   {
		  data[i] = data[parentPos(i)];
		  i = parentPos(i);
	   }
	   data[i] = node;
    }
    else
    {
	   cout << "ERROR ==> heap is full." << endl;
	   exit(1);
    }
}

//----------------------------------- HUFFMAN ALGORITHM IMPLEMENTATION --------------------------------------//

Node* MinPQ::Huffman(int size)
{
    //Q's order has to be fixed (as a complete tree sorted by key's frequency.
    MinPQ Q(this->data, size); 

    //build huffman tree. Each cell is heap by itself.
    Node *curr, *left, *right;
    for (int i = 1; i < size; i++)
    {
	   left = Q.deleteMin(); //delete the minimum priority in Q
	   if (left->getItemKey() != EOF)
	   {
		  left->setLeft(nullptr);
		  left->setRight(nullptr);
	   }

	   right = Q.deleteMin(); //delete the next-minimum priority in Q
	   if (right->getItemKey() != EOF)
	   {
		  right->setLeft(nullptr);
		  right->setRight(nullptr);
	   }
	   
	   int freq = left->getItemFrequency() + right->getItemFrequency();
	   curr = new Node(Item(EOF,freq),left, right);	 //EOF represents nodes that have only frequency ( program stops reading from file when reach to EOF)
	   Q.insertMin(curr);
    }
    return Q.deleteMin(); 
}


//-----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- PRIVATE METHODS ----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//


//FUNCTIONS WHICH RETURN RELATIONS POSITION
int MinPQ::parentPos(int index)	 { return (index - 1) / 2; }
int MinPQ::leftPos(int index)		 { return (2 * index) + 1; }
int MinPQ::rightPos(int index)	 { return (2 * index) + 2; }


//FixHeap (or Heapify) method: fix min-heap order -> minimal value on top
void MinPQ::fixHeap(int startLocToFix)
{
    int minLoc;
    int left = leftPos(startLocToFix);
    int right = rightPos(startLocToFix);

    //Find minimum among node
    minLoc = ((left < heapSize) && (data[left]->getItemFrequency() < data[startLocToFix]->getItemFrequency())) ?
	   left : startLocToFix;
    if ((right < heapSize) && (data[right]->getItemFrequency() < data[minLoc]->getItemFrequency()))
	   minLoc = right;

    if (minLoc != startLocToFix)
    {
	   swap(data[minLoc], data[startLocToFix]);
	   fixHeap(minLoc);
    }
}

//function inserts node into MinPQ.data by inorder.
void MinPQ::convertBSTtoMinPQData(const Node* currBSTNode)
{
    //Insert nodes Inorder style.
    if (currBSTNode->getLeft())
	   convertBSTtoMinPQData(currBSTNode->getLeft());
    insertNodeToData(*currBSTNode);	  //Insert to the next avaliable position into data
    if (currBSTNode->getRight())
	   convertBSTtoMinPQData(currBSTNode->getRight());
}

//function inserts node into MinPQ.data
void MinPQ::insertNodeToData(const Node& nodeToInsert)
{
    data[heapSize] = new Node(*nodeToInsert.getItem(), nullptr, nullptr);
    heapSize += (int)(heapSize < maxSize);
}