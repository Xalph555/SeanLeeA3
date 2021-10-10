/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Dark Knight Class Header File

The Header file for the Dark Knight class Hazard.

**************************************************/

#ifndef KNIGHT_H
#define KNIGHT_H

#include <string>
#include <sstream>
#include <vector>

#include "CommonFuncs.h"
#include "GameEnums.h"
#include "Hazard.h"
#include "Player.h"

using namespace std;


class Knight : public Hazard {
private:
	int damageAmount;

public:
	// constructors and destructors 
	Knight();
	Knight(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious, int damage);
	~Knight();

	// acccessor methods
	int getDamageAmount();
	string getDetails();

	// mutator methods
	void setDamageAmount(int damage);

	// hazard turn update methods
	vector<string> updateInteraction(Player& player);
};



#endif