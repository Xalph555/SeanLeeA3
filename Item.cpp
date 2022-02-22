/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Item Class Definition File

The Definition file for the Item class which contains
the attributes and behaviours of the game's items.

**************************************************/

#include "Item.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Item::Item() {
	itemName = "";
	itemType = NOITEM;
	itemAmount = 0;

	otherData = "";
}


Item::Item(string name, ItemType type, int amount) {
	itemName = name;
	itemType = type;
	itemAmount = amount;

	otherData = "";
}


Item::~Item() {
}



//--------------------------------------//
// accessor methods                     //
//--------------------------------------//

string Item::getName() {
	return itemName;
}


ItemType Item::getType() {
	return itemType;
}


string Item::getTypeName() {
	// returns the name of the item type
	// adapted from Week 6 Lab notes

	switch (getType()) {
		case WEAPON:
			return "Weapon";

		case CONSUMABLE:
			return "Consumable";

		case NAVIGATION:
			return "Map";

		case MAGIC:
			return "Magic";

		default:
			return "No item type has been assigned";
	}
}


int Item::getAmount() {
	return itemAmount;
}


string Item::getOtherData() {
	return otherData;
}


string Item::getDetails() {
	// returns the class details of the item as a formatted string

	stringstream itemDetails;

	itemDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	itemDetails << " Item Name: " << getName() << "\n";
	itemDetails << " Item Type: " << getTypeName() << "\n";
	itemDetails << " Item Amount: " << getAmount() << "\n";
	itemDetails << " Other Data: " << getOtherData() << "\n";
	itemDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return itemDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void Item::setName(string name) {
	if (name.find_first_not_of(' ') != string::npos) {
		itemName = name;

	}
	else {
		displayString(" You have not entered a valid item name to set.\n");
	}
}


void Item::setType(ItemType type) {
	if (type != NULL) {
		itemType = type;

	}
	else {
		displayString(" You have not entered a valid item type to set.\n");
	}
}


void Item::setAmount(int amount) {
	if (amount >= 0) {
		itemAmount = amount;

	}
	else {
		displayString(" You have not entered a valid item amount to set.\n");
	}
}


void Item::setOtherData(string data) {
	if (data.find_first_not_of(' ') != string::npos) {
		otherData = data;

	}
	else {
		displayString(" You have not entered valid other item data to set.\n");
	}
}


void Item::updateAmount(int amount) {
	if (amount != 0) {
		itemAmount += amount;

		if (itemAmount < 0) {
			itemAmount = 0;
		}

	}
	else {
		displayString(" You have not entered a valid amount to update the item's amount.\n");
	}
}