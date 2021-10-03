/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Colony of Corrupted Rats Class Header File

The Header file for the CCRats class Hazard.

**************************************************/

#ifndef CCRATS_H
#define CCRATS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "GameEnums.h"
#include "Room.h"
#include "Hazard.h"
#include "Player.h"

using namespace std;


class CCRats : public Hazard{
private:
	int damageAmount;

public:
	// constructors and destructors 
	CCRats();
	CCRats(string name, HazardType type, string hint, vector<string> description, bool roaming, bool living, int damage);
	~CCRats();

	// acccessor methods
	int getDamageAmount();
	string getDetails();

	// mutator methods
	void setDamageAmount(int damage);

	// hazard turn update methods
	vector<string> updateInteraction(Player& player, vector<Room*>& world);
};



#endif