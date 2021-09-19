/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Player Class Definition File

The Definition file for the Player class which contains
the attributes and behaviours of the Player.

**************************************************/

#include "Player.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Player::Player() {
	playerName = "";
	playerHealthMax = 10;
	playerHealthCurrent = 10;

	currentRoom = 0;
	visitedRooms = {};

	playerInventory = {};

	isDead = false;
	wasDisplaced = false;
}


Player::Player(string name, int healthMax) {
	playerName = name;
	playerHealthMax = healthMax;
	playerHealthCurrent = healthMax;

	currentRoom = 0;
	visitedRooms = {};

	playerInventory = {};

	isDead = false;
	wasDisplaced = false;
} 


Player::~Player() {

}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

string Player::getName() {
	return playerName;
}


int Player::getHealthMax() {
	return playerHealthMax;
}


int Player::getHealthCurrent() {
	return playerHealthCurrent;
}


bool Player::isDisplaced() {
	return wasDisplaced;
}


int Player::getCurrentRoom() {
	return currentRoom;
}


vector<int> Player::getVisitedRooms() {
	return visitedRooms;
}

string Player::getVisitedRoomsAsString() {
	// returns contents of visitedRooms as string
	// adapted from Week 7 Lab notes

	string rooms = "";

	if (!visitedRooms.empty()) {
		vector<int>::const_iterator iter;

		for (iter = visitedRooms.begin(); iter != visitedRooms.end(); iter++) {
			int room = *iter;
			rooms += to_string(room) + ", ";
		}
	}
	else {
		rooms = "The player has not visited any rooms";
	}

	return rooms;
}


vector<Item> Player::getInventory() {
	return playerInventory;
}


string Player::getInventoryAsString() {
	// returns contents of playerInventory as a string
	// adapted from Week 7 Lab notes

	string items = "[";

	if (!playerInventory.empty()) {
		int i = 0;
		for (i; i < playerInventory.size() - 1; i++) {
			items += playerInventory[i].getName() + ", ";
		}

		items += playerInventory[i].getName() + "]";
	}
	else {
		items = "You are not carrying any items.";
	}

	return items;
}


Item* Player::getItem(string name) {
	// finds and returns an item by its name from the player's inventory

	if (!playerInventory.empty()) {
		vector<Item>::iterator iter;

		for (iter = playerInventory.begin(); iter != playerInventory.end(); iter++) {

			if (iter->getName() == name) {
				return &(*iter);
			}
		}

		cout << " The item being retrieved was not found.\n";
		return nullptr;
	}
	else {
		return nullptr;
	}
}


int Player::getItemAmount(string name) {
	return getItem(name)->getAmount();
}


bool Player::hasVisitedRoom(int room) {
	// checks whether the Player has visited the room before

	if (room >= 0) {
		vector<int>::const_iterator iter;

		for (iter = visitedRooms.begin(); iter != visitedRooms.end(); ++iter) {
			int roomIter = *iter;

			if (roomIter == room) {
				return true;
			}
		}

		return false;
	}
	else {
		return false;
	}
}


bool Player::hasItem(string name) {
	// checks to see if the player has the item by name

	Item* item = getItem(name);

	if (item != nullptr) {
		return true;
	}
	else {
		return false;
	}
}


bool Player::hasDied() {
	return isDead;
}


//bool Player::hasGem() {}


string Player::getDetails() {
	// returns details of the player as formatted string

	stringstream playerDetails;

	playerDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	playerDetails << " Player Number: " << getName() << "\n";
	playerDetails << " Player Max Health: " << getHealthMax() << "\n";
	playerDetails << " Player Current Health: " << getHealthCurrent() << "\n";
	playerDetails << " Current Room: " << getCurrentRoom() << "\n";
	playerDetails << " Visited Rooms: " << getVisitedRoomsAsString() << "\n";
	playerDetails << " Inventory: " << getInventoryAsString() << "\n";
	playerDetails << " Is Dead: " << hasDied() << "\n";
	playerDetails << " Was Displaced: " << isDisplaced() << "\n";
	playerDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return playerDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

// set methods
void Player::setName(string name) {
	if (name.find_first_not_of(' ') != string::npos) {
		playerName = name;

	}
	else {
		cout << " You have not entered a valid player name to set.\n";
	}
}


void Player::setHealthMax(int health) {
	if (health > 0) {
		playerHealthMax = health;

	}
	else {
		cout << " You have not entered a valid max health to set.\n";
	}
}


void Player::setHealthCurrent(int health) {
	if (health >= 0) {
		playerHealthCurrent = health;

	}
	else {
		cout << " You have not entered a valid current health to set.\n";
	}
}


void Player::kill() {
	// kills the player

	setHealthCurrent(0);
	isDead = true;
}


void Player::setDisplace(bool displaced) {
	wasDisplaced = displaced;
}


void Player::setStartingRoom(vector<Room*>& world, int room){
	// sets the player's starting room

	if (room >= 0) {
		currentRoom = room;
		world[room]->setPlayerInRoom(true);

	}
	else {
		cout << " You have not entered a starting room to set.\n";
	}
}


void Player::setCurrentRoom(int room) {
	if (room >= 0) {
		currentRoom = room;

	}
	else {
		cout << " You have not entered a valid current room number to set.\n";
	}
}


void Player::setVisitedRooms(vector<int> rooms) {
	if (!rooms.empty()) {
		visitedRooms = rooms;

	}
	else {
		cout << " You have not entered a valid visited rooms vector to set.\n";
	}
}


void Player::setInventory(vector<Item> inventory) {
	if (!inventory.empty()) {
		playerInventory = inventory;

	}
	else {
		cout << " You have not entered a valid inventory vector to set.\n";
	}
}


// update methods
void Player::updateHealthMax(int health) {
	if (health != 0) {
		playerHealthMax += health;

		if (playerHealthMax < 0) {
			playerHealthMax = 0;

		}

	}
	else {
		cout << " You have not entered a valid amount to update max health.\n";
	}
}


void Player::updateHealth(int health) {
	if (health != 0) {
		playerHealthCurrent += health;
		
		if (playerHealthCurrent < 0) {
			playerHealthCurrent = 0;
			isDead = true;

		}
		else if (playerHealthCurrent > playerHealthMax) {
			playerHealthCurrent = playerHealthMax;
		}

	}
	else {
		cout << " You have not entered a valid amount to update current health.\n";
	}
}


void Player::updateCurrentRoom(int room) {
	if (room >= 0) {
		updateVisitedRooms(currentRoom);
		currentRoom = room;
		updateVisitedRooms(room);

	}
	else {
		cout << " You have not entered a valid room number to update current room.\n";
	}
}


void Player::updateVisitedRooms(int room) {
	if (!hasVisitedRoom(room)) {
		visitedRooms.push_back(room);
	}
}


void Player::updateInventory(Item item){
	if (item.getType() != NOITEM) {
		playerInventory.push_back(item);

	}
	else {
		cout << " You have not entered a valid item to add to the inventory.\n";
	}
}


void Player::updateItem(string name, int amount){
	Item* item = getItem(name);

	if (item != nullptr) {
		item->updateAmount(amount);
	}
	else {
		cout << " The item to update could not be found.\n";
	}

}



//-------------------------------------//
// player action methods               //
//-------------------------------------//

void Player::moveTo(vector<Room*>& world, int room){
	// moves the player to the desired room and updates the appropriate rooms

	world[currentRoom]->setPlayerInRoom(false);
	updateCurrentRoom(room);
	world[room]->setPlayerInRoom(true);
}


//vector<string> Player::shootBolt(vector<Room*>& world, string direction){}


//void Player::teleportTo(vector<Room*>& world, int room){}