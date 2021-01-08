#include "Item.h"
using namespace std;

//CONSTRUCTORS
Item::Item(KeyType key, DataType freq)
{
    this->key = key;
    this->frequency = freq;
}

Item::Item(const Item& other) { *this = other; }

//DESTRUCTOR
Item::~Item() {}

//-------------------------------------------- GENERAL METHODS ----------------------------------------------//

const Item& Item::operator=(const Item& other)
{
    if (this != &other)
    {
	   this->key = other.key;
	   this->frequency = other.frequency;
    }
    return *this;
}

//GETTERS
KeyType Item::getKey() const			{ return key; }
DataType Item:: getFrequency() const	{ return frequency; }

//SETTERS
void Item::setKey(KeyType key)		{ this->key = key; }
void Item::setFrequency(DataType freq)	{ this->frequency = freq; }