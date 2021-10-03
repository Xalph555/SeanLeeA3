/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Room Class Header File

The Header file for the Room class which contains
the attributes and behaviours of the locations
in the Abandoned Ruins.

**************************************************/

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "GameEnums.h"

using namespace std;


class Room {
private:
	int roomNumber;
	string roomName;
	string roomDescription;
	vector<string> roomExitDirections;
	vector<int> roomExitConnections;

	bool hasPlayer;
	vector<int> hazards;


public:
	// constructors and destructors 
	Room();
	Room(int num, string name, string description, vector<string> exitDir, vector<int> exitConnections);
	~Room();

	// accessor methods
	int getNumber();
	string getName();
	string getDescription();
	vector<string> getExitDirections();
	string getExitDirectionsAsString();
	vector<int> getExitConnections();
	string getExitConnectionsAsString();
	int getRoomConnection(string direction);
	bool isPlayerInRoom();
	vector<int> getHazards();
	string getHazardsAsString();
	bool hasHazard();

	string getRoomInfo();
	string getRoomExits();
	string getDetails();

	// mutator methods
	void setNumber(int num);
	void setName(string name);
	void setDescription(string description);
	void setExitDirections(vector<string> directions);
	void setExitConnections(vector<int> connections);
	void setPlayerInRoom(bool isInRoom);
	void setHazards(vector<int> hazards);
	void addHazard(int hazard);
	void removeHazard(int hazard);

};



#endif
