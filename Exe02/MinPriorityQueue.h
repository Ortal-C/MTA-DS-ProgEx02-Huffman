#ifndef __MINPRIORITYQUEUE_H
#define __MINPRIORITYQUEUE_H
#include <iostream>
#include "Node.h"

class MinPQ
{
private:
    //PRIVATE CLASS MEMBERS
    Node** data;
    int maxSize;
    int heapSize;
    bool allocated;

public:
    MinPQ(int size);
    MinPQ(Node** staticTree, int n);	  //constructor known also as BuildHeap operation => Floyd's Algorithm
    ~MinPQ();
    MinPQ(const MinPQ& other) = delete;
    const MinPQ& operator=(const MinPQ& other) = delete;

    //GENERAL
    void makeEmpty();
    bool isEmpty() const;

    //GETTERS
    int getHeapSize() const;
    int getMaxSize() const;
    bool isDataAllocated() const;
    
    //PRIORITY-QUEUE OPERATIONS
    Node** min() const;
    Node*&  deleteMin();
    void insertMin(Node*& left, Node*& right);

private:
    //PRIVATE METHODS
    int parentPos(int index);
    int leftPos(int index);
    int rightPos(int index);
    void fixHeap(int startLocToFix);
    void heapSort(Node** const data, int n);
};
#endif // !__MINPRIORITYQUEUE_H