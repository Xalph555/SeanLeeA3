/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Outcasted Raiders Class Header File

The Header file for the Outcasted Raiders class Hazard.

**************************************************/

#ifndef RAIDERS_H
#define RAIDERS_H

#include <string>
#include <sstream>
#include <vector>

#include "CommonFuncs.h"
#include "GameEnums.h"
#include "RoomContainer.h"
#include "Hazard.h"
#include "Player.h"

using namespace std;


class Raiders : public Hazard {
private:
	int damageAmount;


public:
	// constructors and destructors 
	Raiders();
	Raiders(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious, int damage);
	~Raiders();

	// acccessor methods
	int getDamageAmount();
	string getDetails();

	// mutator methods
	void setDamageAmount(int damage);

	// hazard turn update methods
	vector<string> updateInteraction(Player& player, RoomContainer& world);
};



#endif