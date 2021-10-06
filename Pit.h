/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Bottomless Pit Class Header File

The Header file for the Bottomless Pit class Hazard.

**************************************************/

#ifndef PIT_H
#define PIT_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "GameEnums.h"
#include "Hazard.h"
#include "Player.h"

using namespace std;


class Pit : public Hazard {
private:

public:
	// constructors and destructors 
	Pit();
	Pit(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious);
	~Pit();

	// hazard turn update methods
	vector<string> updateInteraction(Player & player);
};



#endif