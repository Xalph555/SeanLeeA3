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

#include "GameEnums.h"
#include "Room.h"
#include "Item.h"
#include "HazardContainer.h"

using namespace std;


class Player {
private:
	string playerName;
	int playerHealthMax;
	int playerHealthCurrent;

	int currentRoom;
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
	vector<int> getVisitedRooms();
	string getVisitedRoomsAsString();
	vector<Item> getInventory();
	string getInventoryAsString();
	Item* getItem(string name);
	int getItemAmount(string name);
	bool hasVisitedRoom(int room);
	bool hasItem(string name);
	bool hasDied();
	//bool hasGem();
	string getDetails();

	// mutator set methods
	void setName(string name);
	void setHealthMax(int health);
	void setHealthCurrent(int health);
	void setDisplace(bool displaced);
	void setIsDead(bool dead);
	void kill();
	void setStartingRoom(vector<Room*>& world, int room);
	void setCurrentRoom(int room);
	void setVisitedRooms(vector<int> rooms);
	void setInventory(vector<Item> inventory);

	// mutator update methods
	void updateHealthMax(int health);
	void updateHealth(int health);
	void updateCurrentRoom(int room);
	void updateVisitedRooms(int room);
	void updateInventory(Item item);
	void updateItem(string name, int amount);

	// player action methods
	void moveTo(vector<Room*>& world, int room);
	vector<string> shootBolt(vector<Room*>& world, HazardContainer& hazards, vector<string> path);
	//void teleportTo(vector<Room*>& world, int room);
};



#endif