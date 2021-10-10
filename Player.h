/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Player Class Header File

The Header file for the Player class which contains
the attributes and behaviours of the Player.

**************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "GameEnums.h"
#include "RoomContainer.h"
#include "Item.h"
#include "HazardContainer.h"

using namespace std;


class Player {
private:
	string playerName;
	int playerHealthMax;
	int playerHealthCurrent;

	int currentRoom;
	int displacedRoom;
	vector<int> visitedRooms;

	vector<Item> playerInventory;

	bool wasDisplaced;
	bool isDead;


public:
	// constructors and destructors 
	Player();
	Player(string name, int healthMax);
	~Player();

	// accessor methods
	string getName();
	int getHealthMax();
	int getHealthCurrent();
	bool isDisplaced();
	int getCurrentRoom();
	int getDisplacedRoom();
	vector<int> getVisitedRooms();
	string getVisitedRoomsAsString();
	vector<Item> getInventory();
	string getInventoryAsString();
	Item* getItem(string name);
	int getItemAmount(string name);
	bool hasVisitedRoom(int room);
	bool hasItem(string name);
	bool hasDied();
	string getDetails();

	// mutator set methods
	void setName(string name);
	void setHealthMax(int health);
	void setHealthCurrent(int health);
	void setDisplace(bool displaced);
	void setIsDead(bool dead);
	void kill();
	void setStartingRoom(RoomContainer& world, int room);
	void setCurrentRoom(int room);
	void setDisplacedRoom(int room);
	void setVisitedRooms(vector<int> rooms);
	void setInventory(vector<Item> inventory);

	// mutator update methods
	void updateHealthMax(int health);
	void updateHealth(int health);
	void updateCurrentRoom(int room);
	void updateDisplacement();
	void updateVisitedRooms(int room);
	void updateInventory(Item item);
	void updateItem(string name, int amount);

	// player action methods
	void moveTo(RoomContainer& world, int room, bool displaced);
	vector<string> shootBolt(RoomContainer& world, HazardContainer& hazards, vector<string> path);
};



#endif