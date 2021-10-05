/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Suspicious Trader Class Header File

The Header file for the Suspicious Trader class Hazard.

**************************************************/

#ifndef TRADER_H
#define TRADER_H

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


class Trader : public Hazard {
private:

public:
	// constructors and destructors 
	Trader();
	Trader(string name, HazardType type, string hint, vector<string> description, bool roaming, bool living);
	~Trader();

	// hazard turn update methods
	vector<string> updateInteraction(Player& player, vector<Room*>& world);
};



#endif