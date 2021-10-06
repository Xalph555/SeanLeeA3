/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Opportunistic Thief Class Header File

The Header file for the Opportunistic Thief class Hazard.

**************************************************/

#ifndef THIEF_H
#define THIEF_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "GameEnums.h"
#include "Hazard.h"
#include "Room.h"
#include "Item.h"
#include "Player.h"

using namespace std;


class Thief : public Hazard {
private:

public:
	// constructors and destructors 
	Thief();
	Thief(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious);
	~Thief();

	// hazard turn update methods
	vector<string> updateInteraction(Player & player, vector<Room*>&world);
};



#endif