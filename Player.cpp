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
	displacedRoom = -1;
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
	displacedRoom = -1;
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


int Player::getDisplacedRoom() {
	return displacedRoom;
}


vector<int> Player::getVisitedRooms() {
	return visitedRooms;
}

string Player::getVisitedRoomsAsString() {
	// returns contents of visitedRooms as a string
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
		unsigned int i = 0;
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

		return nullptr;

	}
	else {
		return nullptr;
	}
}


int Player::getItemAmount(string name) {
	// returns the amount of the input item the player has

	if (hasItem(name)) {
		return getItem(name)->getAmount();
	}

	return 0;
}


bool Player::hasItem(string name) {
	// checks to see if the player has the input item by name

	Item* item = getItem(name);

	if (item != nullptr) {
		return true;
	}
	else {
		return false;
	}
}


bool Player::hasVisitedRoom(int room) {
	// checks whether the Player has visited the input room before

	if (room >= 0) {
		vector<int>::const_iterator iter;

		if (find(visitedRooms.begin(), visitedRooms.end(), room) != visitedRooms.end()) {
			return true;

		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}


bool Player::hasDied() {
	return isDead;
}


string Player::getDetails() {
	// returns the class details of the player as formatted string

	stringstream playerDetails;

	playerDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	playerDetails << " Player Name: " << getName() << "\n";
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
		displayString(" You have not entered a valid player name to set.\n");
	}
}


void Player::setHealthMax(int health) {
	if (health > 0) {
		playerHealthMax = health;

	}
	else {
		displayString(" You have not entered a valid max health to set.\n");
	}
}


void Player::setHealthCurrent(int health) {
	if (health >= 0) {
		playerHealthCurrent = health;

	}
	else {
		displayString(" You have not entered a valid current health to set.\n");
	}
}


void Player::setIsDead(bool dead) {
	isDead = dead;
}


void Player::kill() {
	// kills the player

	setHealthCurrent(0);
	isDead = true;
}


void Player::setDisplace(bool displaced) {
	wasDisplaced = displaced;
}


void Player::setStartingRoom(RoomContainer& world, int room){
	// sets the player's starting room

	if (room >= 0) {
		currentRoom = room;
		world.getRoom(room)->setPlayerInRoom(true);

	}
	else {
		displayString(" You have not entered a starting room to set.\n");
	}
}


void Player::setCurrentRoom(int room) {
	if (room >= 0) {
		currentRoom = room;

	}
	else {
		displayString(" You have not entered a valid current room number to set as the current room.\n");
	}
}


void Player::setDisplacedRoom(int room) {
	if (room >= 0) {
		displacedRoom = room;

	}
	else {
		displayString(" You have not entered a valid current room number to set as the displaced room.\n");
	}
}


void Player::setVisitedRooms(vector<int> rooms) {
	if (!rooms.empty()) {
		visitedRooms = rooms;

	}
	else {
		displayString(" You have not entered a valid visited rooms vector to set.\n");
	}
}


void Player::setInventory(vector<Item> inventory) {
	if (!inventory.empty()) {
		playerInventory = inventory;

	}
	else {
		displayString(" You have not entered a valid inventory vector to set.\n");
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
		displayString(" You have not entered a valid amount to update max health.\n");
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
		displayString(" You have not entered a valid amount to update current health.\n");
	}
}


void Player::updateCurrentRoom(int room) {
	if (room >= 0) {
		updateVisitedRooms(currentRoom);
		currentRoom = room;
		updateVisitedRooms(room);

	}
	else {
		displayString(" You have not entered a valid room number to update current room.\n");
	}
}


void Player::updateDisplacement() {
	// updates the player's displacement status to reflect any displacement caused by being forcefully moved to another room
	// e.g. when they are moved by the CCRats or the Raiders

	if (displacedRoom != -1) {
		updateVisitedRooms(currentRoom);
		currentRoom = displacedRoom;
		displacedRoom = -1;
		updateVisitedRooms(displacedRoom);
		wasDisplaced = false;

	}
	else {
		displayString(" There was no valid displacement room set despite the player being displaced.\n");
	}
}



void Player::updateVisitedRooms(int room) {
	if (!hasVisitedRoom(room)) {
		visitedRooms.push_back(room);
	}
}


void Player::updateInventory(Item item){
	// adds an item to the player's inventory

	if (item.getType() != NOITEM) {
		playerInventory.push_back(item);

	}
	else {
		displayString(" You have not entered a valid item to add to the inventory.\n");
	}
}


void Player::updateItem(string name, int amount){
	// updates the amount of an item in the player's inventory

	if (hasItem(name)) {
		getItem(name)->updateAmount(amount);

	}
	else {
		displayString(" The item to update could not be found.\n");
	}
}



//-------------------------------------//
// player action methods               //
//-------------------------------------//

void Player::moveTo(RoomContainer& world, int room, bool displaced){
	// moves the player to the desired room and updates the appropriate rooms

	if (displaced) {
		wasDisplaced = true;

		world.getRoom(currentRoom)->setPlayerInRoom(false);
		setDisplacedRoom(room);
		world.getRoom(room)->setPlayerInRoom(true);

	}
	else {
		world.getRoom(currentRoom)->setPlayerInRoom(false);
		updateCurrentRoom(room);
		world.getRoom(room)->setPlayerInRoom(true);

		getItem("Incense Sticks")->updateAmount(-1);
	}
}


vector<string> Player::shootBolt(RoomContainer& world, HazardContainer& hazards, vector<string> path){
	// fires crossbow bolt along the specified path

	vector<string> boltHints;

	if (path.size() > 0 && path.size() < 6) {
		int currentBoltRoom = getCurrentRoom();

		getItem("Crossbow Bolts")->updateAmount(-1);

		for (unsigned int i = 0; i < path.size(); i++) {
			string dir = path[i];

			boltHints.push_back(" Room " + to_string(i) + ":");

			int targetRoom = world.getRoom(currentBoltRoom)->getRoomConnection(dir);

			// move to random room due to invalid input direction
			if (targetRoom == -1) {
				vector<int> availableExits = world.getRoom(currentBoltRoom)->getExitConnections();

				targetRoom = availableExits[rand() % availableExits.size()];
				boltHints.push_back(" The bolt had to take a detour.\n");
			}

			// get room hint
			if (world.getRoom(targetRoom)->hasHazard()) {
				boltHints.push_back(" The bolt senses something in this room.\n");

			}
			else {
				boltHints.push_back(" The bolt could not sense anything in this room.\n");
			}

			currentBoltRoom = targetRoom;

			// check if player has hit themselves
			if (currentBoltRoom == getCurrentRoom()) {
				boltHints.push_back(" You feel a sharp pain as a bolt pierces your back.\n");
				kill();
				break;
			}

			// check if the player has hit the arigamo
			if (currentBoltRoom == hazards.getHazard("Arigamo")->getCurrentRoom()) {
				hazards.getHazard("Arigamo")->kill();
				boltHints.push_back(hazards.getHazard("Arigamo")->getEventDescriptions()[2]);
				break;
			}
		}

		// check if the arrow has landed in an adjacent room to the arigamo
		vector<int> arigamoAdjRoom = { hazards.getHazard("Arigamo")->getCurrentRoom() };

		if (world.isEntityInAdjRoom(arigamoAdjRoom, currentBoltRoom)) {
			hazards.getHazard("Arigamo")->setIsConscious(true);
		}
	}

	return boltHints;
}