#include "MinPriorityQueue.h"

//-----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- PUBLIC METHODS -----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//

//CONSTRUCTOR
MinPQ::MinPQ(int size) : heapSize(0), maxSize(size)
{
    data = new Node*[maxSize];
    allocated = true;
}

//DESTRUCTOR
MinPQ::~MinPQ()
{
    if (allocated)
	   delete[] data;
    data = nullptr;
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


//------------------------------------------------- GENERAL -------------------------------------------------//

bool MinPQ::isEmpty() const		 { return heapSize == 0; }

void MinPQ::makeEmpty()
{
    if (allocated)
	   delete[] data;
}


void MinPQ::heapSort(Node** const data, int n)
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
Node*& MinPQ::deleteMin()
{
    if (heapSize >= 1)
    {
	   heapSize--;
	   swap(data[0], data[heapSize]);
	   fixHeap(0);
	   return data[heapSize];
    }
    else
    {
	   cout << "ERROR ==> heap is empty." << endl;
	   exit(1);
    }
}
//Function creates and inserts new-node into heap and fix its order
void MinPQ::insertMin(Node*& left, Node*& right)
{
    if (heapSize <= maxSize)
    {
	   //create newNode (left and right are its children).
	   int i = heapSize;
	   int freq = left->getFrequency() + right->getFrequency();
	   Node *newNode = new Node(EOF, freq, left,right);

	   //fix heap-order so we can insert newNode to correct position.
	   while (i > 0 && (data[parentPos(i)]->getFrequency() > freq))
	   {
		  swap(data[i],data[parentPos(i)]);
		  i = parentPos(i);
	   }
	   if (data[i])
		  delete data[i];
	   this->data[i] = newNode;
	   heapSize++;
    }
    else
    {
	   cout << "ERROR ==> heap is full." << endl;
	   exit(1);
    }
}

//-----------------------------------------------------------------------------------------------------------//
//-------------------------------------------- PRIVATE METHODS ----------------------------------------------//
//-----------------------------------------------------------------------------------------------------------//


//FUNCTIONS WHICH RETURN RELATIONS POSITIONS
int MinPQ::parentPos(int index)	 { return ((index - 1) / 2); }
int MinPQ::leftPos(int index)		 { return ((2 * index) + 1); }
int MinPQ::rightPos(int index)	 { return ((2 * index) + 2); }

//FixHeap (known also as Heapify) method: fix min-heap order -> minimal value on top
void MinPQ::fixHeap(int node)
{
    int min = node;
    int left = leftPos(node);
    int right = rightPos(node);

    // find minimum among node, left and right.
    if ((left < heapSize) && (data[left]->getFrequency() < data[node]->getFrequency()))
	   min = left;

    if ((right < heapSize) && (data[right]->getFrequency() < data[min]->getFrequency()))
	   min = right;

    if (min != node)
    {
	   swap(data[node], data[min]);
	   fixHeap(min);
    }
}   