#ifndef __ITEM_H
#define __ITEM_H
#include <iostream>
using namespace std;

typedef char KeyType;
typedef int  DataType;

class Item
{
private:
    //PRIVATE CLASS MEMBERS
    KeyType key;
    DataType frequency;

public:
    Item(KeyType key, DataType freq = 1);
    Item(const Item& other);
    ~Item();

    const Item& operator=(const Item& other);

    //GETTERS
    KeyType getKey() const;
    DataType getFrequency() const;

    //SETTERS
    void setKey(KeyType key);
    void setFrequency(DataType freq);

    //FRIEND CLASS DECLARATION
    friend class Node;
};
#endif // !__ITEM_H