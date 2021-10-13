/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Corrupted Oracle Class Header File

The Header file for the Corrupted Oracle class Hazard.

**************************************************/

#ifndef ORACLE_H
#define ORACLE_H

#include <string>
#include <sstream>
#include <vector>

#include "CommonFuncs.h"
#include "GameEnums.h"
#include "Hazard.h"
#include "Item.h"
#include "Player.h"

using namespace std;


class Oracle : public Hazard {
public:
	// constructors and destructors 
	Oracle();
	Oracle(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious);
	~Oracle();

	// hazard turn update methods
	vector<string> updateInteraction(Player & player);
	void roomInteraction(Player& player, int arigamoRoom);
};



#endif