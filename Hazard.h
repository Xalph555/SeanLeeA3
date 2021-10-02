/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Hazard Class Header File

The Header file for the Hazard class which
serves as the base class for the game's hazards and
opponents.

**************************************************/

#ifndef HAZARD_H
#define HAZARD_H

#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <vector>

#include "GameEnums.h"
#include "Room.h"
#include "Item.h"

using namespace std;


class Hazard {
private:
	static int numHazards;


protected:
	int hazardID;
	string hazardName;
	HazardType hazardType;
	int currentRoom;
	string hazardHint;

	vector<string> eventDescriptions;

	Item fuhaiGem;

	bool isRoamingType;
	bool isLivingType;
	bool isDead;


public:
	// static accessors
	static int getNumHazards();

	// constructors and destructors
	Hazard();
	Hazard(string name, HazardType type, string hint, vector<string> descriptions, bool roaming, bool living);
	virtual ~Hazard();

	// accessor methods
	int getID();
	string getName();
	HazardType getType();
	string getTypeAsString();
	int getCurrentRoom();
	string getHint();
	vector<string> getEventDescriptions();
	string getDescriptionsAsString();
	bool hasGem();
	bool isRoaming();
	bool IsLiving();
	bool hasDied();

	virtual string getDetails();

	// mutator set methods
	void setID(int ID);
	void setName(string name);
	void setType(HazardType type);
	void setStartingRoom(vector<Room*>&world, int room);
	void setCurrentRoom(int room);
	void setHint(string hint);
	void setEventDescriptions(vector<string> events);
	void setGem(Item gem);
	void setRoamingType(bool isRoaming);
	void setLivingType(bool living);
	void setIsDead(bool dead);
	void kill();

	// movement methods
	void moveTo(vector<Room*>&world, int room);

	// interaction methods
	virtual vector<string> updateInteraction();
	virtual void roomInteraction();
};


#endif