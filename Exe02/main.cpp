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
#include <stdlib.h>
#include <string>
#include "BSTree.h"
#include "BinaryTree.h"
#include "MinPriorityQueue.h"
using namespace std;

//----------------------------------------- FUNCTIONS DECLARATION -------------------------------------------//

static int weight = 0;	   //initial file-weight = 0
void errorOpenFile();
void printHuffmanCode(Node* const currNode);
void calcCodes(Node* currNode, string& str);

//-----------------------------------------------------------------------------------------------------------//

//if here => can't open file with the enterd filename.
void errorOpenFile()
{
    cout << "invalid input." << endl;
    exit(1);
}

//-----------------------------------------------------------------------------------------------------------//

//function prints each node's letter and its corresponding code (using helper) and print file's weight.
void printHuffmanCode(Node* const currNode)
{
    cout << "Character encoding:" << endl;
    string str;
    if (!currNode->getLeft() && !currNode->getRight())	  //case 1: currNode is a leaf with one letter only.
    {
	   str = "1";
	   weight = currNode->getItemFrequency();
	   cout << "'" << currNode->getItemKey() << "' - " << str << endl;
    }

    else
	   calcCodes(currNode, str);

    //printing weight
    cout << "\nEncoded file weight:" << weight << " bits" << endl;
}

//-----------------------------------------------------------------------------------------------------------//

//function calculates file-weight and prints each node's letter and its corresponding code (recursive helper to printHuffmanCode). 
void calcCodes(Node* currNode, string& str)
{
    if (currNode->getItemKey() != EOF) //currNode's key is a character.
    {
	   weight += (str.length() * currNode->getItemFrequency());
	   cout << "'" << currNode->getItemKey() << "' - " << str << endl;;
	   str.pop_back();	   //remove the last binary-digit in string
    }

    else
    {
	   if (currNode->getLeft())
	   {
		  str.append("0");
		  calcCodes(currNode->getLeft(), str);
	   }

	   if (currNode->getRight())
	   {
		  str.append("1");
		  calcCodes(currNode->getRight(), str);
	   }

	   // if here => done handling with left and right children
	   if (!str.empty())
		  str.pop_back(); //can erase the last binary-digit in string (only if string contains digits).
    }
}

//-----------------------------------------------------------------------------------------------------------//

int main()
{
    string fileName;
    cout << "Please enter a file name and its type (in format of FILENAME.TYPE) and then press enter: ";
    getline(cin, fileName);

    //open file and check errors
    ifstream theFile;
    theFile.open(fileName);
    if (!theFile)
	   errorOpenFile();

    //------------------ Build binary-search-tree from file's letters and their frequency -----------------------//

    //if here => file opened successfully.
    BSTree ST;
    char keyToInsert;
    while (!theFile.get(keyToInsert).eof())
	   ST.Insert(keyToInsert);

    //ST has all the file's letters and frequencies now.
    int nodesNum = ST.numOfNodes;
    theFile.close();

    //------------------------------------ Implementing Huffman algorithm ---------------------------------------//

    //convert binary-search-tree ST to Minimum priority queue. 
    MinPQ heap(ST);

    //Implement Huffman code according to heap's data and prints letters' code and file-weight
    Node* result = heap.Huffman(nodesNum);
    printHuffmanCode(result); //printing letters' code and file-weight
    return 0;
}
