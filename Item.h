/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Item Class Header File

The Header file for the Item class which contains
the attributes and behaviours of the game's items.

**************************************************/

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <sstream>
#include <vector>

#include "CommonFuncs.h"
#include "GameEnums.h"

using namespace std;


class Item {
private:
	string itemName;
	ItemType itemType;
	int itemAmount;

	string otherData;


public:
	// constructors and destructors 
	Item();
	Item(string name, ItemType type, int amount);
	~Item();

	// accessor methods
	string getName();
	ItemType getType();
	string getTypeName();
	int getAmount();
	string getOtherData();
	string getDetails();

	// mutator methods
	void setName(string name);
	void setType(ItemType type);
	void setAmount(int amount);
	void setOtherData(string data);
	void updateAmount(int amount);
};



#endif