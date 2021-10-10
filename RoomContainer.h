/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Room Container Class Header File

The Header file for the Room Container class which
serves as a customer container for the game's rooms.

**************************************************/

#ifndef ROOMCONTAINER_H
#define ROOMCONTAINER_H

#include <vector>
#include <algorithm>

#include "CommonFuncs.h"
#include "GameEnums.h"
#include "Room.h"

using namespace std;

class RoomContainer {
private:
	vector<Room*> rooms;

public:
	// constructors and destructors
	RoomContainer();
	~RoomContainer();

	// accessor methods
	Room* getRoom(int room);
	int getNumRooms();
	int findRandomEmptyStartRoom(vector<int> exceptionRooms);
	int findEmptyAdjRoom(int currentRoom, vector<int> exceptionRooms);
	bool isEntityInAdjRoom(vector<int> entityRooms, int room);

	// mutator methods
	void addRoom(Room* room);
	void removeRoom(int room);
};



#endif