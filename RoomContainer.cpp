/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Room Container Class Definition File

The Definition file for the Room Container class which
serves as a custom container for the game's rooms.

**************************************************/

#include "RoomContainer.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

RoomContainer::RoomContainer(){
	rooms = {};
}


RoomContainer::~RoomContainer() {
	// removing pointers from heap
	for (int i = rooms.size() - 1; i >= 0; --i) {
		delete rooms[i];
		rooms[i] = nullptr;
	}
}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

Room* RoomContainer::getRoom(int room) {
	// finds and returns the first pointer to the room from the room collection based on the given room number

	vector<Room*>::const_iterator iter;

	for (iter = rooms.begin(); iter != rooms.end(); iter++) {
		if ((*iter)->getNumber() == room) {
			return &(**iter);
		}
	}

	return nullptr;
}


int RoomContainer::getNumRooms() {
	return rooms.size();
}


int RoomContainer::findRandomEmptyStartRoom(vector<int> exceptionRooms) {
	// finds and returns a random room that does not have a hazard or player in it or adjacent to it

	int room = rand() % rooms.size();

	while (getRoom(room)->hasHazard() || getRoom(room)->isPlayerInRoom() || isEntityInAdjRoom(exceptionRooms, room)) {
		room = rand() % rooms.size();
	}

	return room;
}


int RoomContainer::findEmptyAdjRoom(int currentRoom, vector<int> exceptionRooms) {
	// returns the next available adjacent room that does not have a hazard excluding exception rooms

	int room = -1;
	vector<int> availbleRooms;

	vector<int> connectedRooms = getRoom(currentRoom)->getExitConnections();
	vector<int>::const_iterator iter;

	for (iter = connectedRooms.begin(); iter != connectedRooms.end(); iter++) {
		int roomTemp = *iter;

		if (!getRoom(roomTemp)->hasHazard() || find(exceptionRooms.begin(), exceptionRooms.end(), roomTemp) != exceptionRooms.end()) {
			availbleRooms.push_back(roomTemp);
		}
	}

	if (!availbleRooms.empty()) {
		room = availbleRooms[rand() % availbleRooms.size()];
	}

	return room;
}


bool RoomContainer::isEntityInAdjRoom(vector<int> entityRooms, int room) {
	// checks whether the entity's room is adjacent to the input room

	vector<int> connectedRooms = getRoom(room)->getExitConnections();
	vector<int>::const_iterator iter;

	for (iter = connectedRooms.begin(); iter != connectedRooms.end(); iter++) {
		int roomTemp = *iter;

		if (find(entityRooms.begin(), entityRooms.end(), roomTemp) != entityRooms.end()) {
			return true;
		}
	}

	return false;
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void RoomContainer::addRoom(Room* room) {
	// adds the input room to the room collection

	if (room != nullptr) {
		rooms.push_back(room);

	}
	else {
		displayString(" You have not entered a valid room to add to the container.\n");
	}
}


void RoomContainer::removeRoom(int room) {
	// removes a specific room from the room collection based on the give room number

	vector<Room*>::iterator iter;

	for (iter = rooms.begin(); iter != rooms.end(); iter++) {
		if ((*iter)->getNumber() == room) {
			delete (*iter);
			*iter = nullptr;
			rooms.erase(iter);

			break;
		}
	}

	displayString(" You have not entered a valid room to remove from the container.\n");
}