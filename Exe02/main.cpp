/**********************************************************************************
 ********************* MTA DATA STRUCTURES COURSE PROJECT 2 ***********************
 ************* IMPLEMENTING HUFFMAN CODE WITH MINIMUM PRIORITY QUEUE **************
 ********************************************************************************** /

/*  The program receives file-name (with .txt extension) and prints the 
    corresponding Huffman code for each letter in the file and weight.
    NOTE: Code is calculated according to letters' frequencies.				    */

//-----------------------------------------------------------------------------------------------------------//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "BSTree.h"
#include "BinaryTree.h"
#include "MinPriorityQueue.h"
using namespace std;

//----------------------------------------- FUNCTIONS DECLARATION -------------------------------------------//

void errorOpenFile();
Node* Huffman(MinPQ& heap, int size);
void printHuffmanCode(Node* const currNode);
void calcCodes(Node* currNode, string& str, int& weight);

//-----------------------------------------------------------------------------------------------------------//

//if here => can't open file with the enterd filename.
void errorOpenFile()
{
    cout << "invalid input." << endl;
    exit(1);
}

//----------------------------------- HUFFMAN ALGORITHM IMPLEMENTATION --------------------------------------//

Node* Huffman(MinPQ& heap, int size)
{
    //build huffman tree. Each cell is heap by itself.
    Node *left, *right;
    for (int i = 1; i < size; i++)
    {
	   left = heap.deleteMin(); //delete the minimum priority node in heap
	   if (left->getKey() != EOF)
	   {
		  left->setLeft(nullptr);
		  left->setRight(nullptr);
	   }
	   right = heap.deleteMin(); //delete the next-minimum priority node in heap
	   if (right->getKey() != EOF)
	   {
		  right->setLeft(nullptr);
		  right->setRight(nullptr);
	   }
	   
	   heap.insertMin(left, right);
    }
    return heap.deleteMin();
}

//-----------------------------------------------------------------------------------------------------------//

//function prints each node's letter and its corresponding code (using helper) and print file's weight.
void printHuffmanCode(Node* const currNode)
{
    int weight = 0;	   //initial file-weight = 0
    cout << "Character encoding:" << endl;
    string str;
    if (!currNode->getLeft() && !currNode->getRight())	  //case 1: currNode is a leaf with one letter only.
    {
	   str = "1";
	   weight = currNode->getFrequency();
	   cout << "'" << currNode->getKey() << "' - " << str << endl;
    }

    else
	   calcCodes(currNode, str, weight);

    //printing weight
    cout << "\nEncoded file weight: " << weight << " bits" << endl;
}

//-----------------------------------------------------------------------------------------------------------//

//function calculates file-weight and prints each node's letter and its corresponding code (recursive helper to printHuffmanCode). 
void calcCodes(Node* currNode, string& str, int& weight)
{
    if (currNode->getKey() != EOF) //currNode's key is a character.
    {
	   char c = currNode->getKey();
	   if (c == '\n' || c == '\t')
		  (c == '\n') ? cout << "'\\n'" : cout << "'\\t'";
	   else
		  cout << "'" << c << "'";
	   cout << " - " << str << endl;
	   weight += (str.length() * currNode->getFrequency());
	   str.pop_back();	   //remove the last binary-digit in string
    }

    else
    {
	   if (currNode->getLeft())
	   {
		  str.append("0");
		  calcCodes(currNode->getLeft(), str, weight);
	   }

	   if (currNode->getRight())
	   {
		  str.append("1");
		  calcCodes(currNode->getRight(), str, weight);
	   }

	   // if here => done handling with left and right children
	   if (!str.empty())
		  str.pop_back(); //can erase the last binary-digit in string (only if string contains digits).
    }
}

//-----------------------------------------------------------------------------------------------------------//

int main()
{
    char fileName[MAX_STR_SIZE];
    cout << "Please enter a file name and its type (in format of FILENAME.TYPE) and then press enter: ";
    cin >> fileName;

    //open file and check errors
    ifstream theFile;
    theFile.open(fileName);
    if (!theFile)
	   errorOpenFile();

    //------------------ Build binary-search-tree from file's letters and their frequency -----------------------//

    //if here => file opened successfully. Now, reading char by char from file and insert each of them to binary-search tree.
    BSTree ST;
    char keyToInsert;
    while (!theFile.get(keyToInsert).eof())
	   ST.Insert(keyToInsert);

    //If here => ST has all the file's letters and frequencies so we can close file.
    int numOfNodes = ST.numOfNodes;
    theFile.close();

    //------------------------------------ Implementing Huffman algorithm ---------------------------------------//

    //convert binary-search-tree ST to static array. 
    Node** staticArr = new Node*[numOfNodes];
    ST.convertToArray(staticArr);

    //Implementing Huffman code and printing letters, their corresponding codes and file-weight.
    MinPQ heap(staticArr, numOfNodes);
    Node* huffmanTreeRoot = new Node(*Huffman(heap, numOfNodes));
    printHuffmanCode(huffmanTreeRoot);

    //-----------------------------------------------------------------------------------------------------------//

    //delete huffmanTreeRoot allocation.
    delete huffmanTreeRoot;
    huffmanTreeRoot = nullptr;

    //delete staticArr allocation.
    for (int i = 0; i < numOfNodes; i++)
	   delete staticArr[i];
    delete[] staticArr;

    return 0;
}
