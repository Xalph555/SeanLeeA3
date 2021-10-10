/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Hazard Container Class Header File

The Header file for the Hazard Container class which
serves as a customer container for the game's hazards.

**************************************************/

#ifndef HAZARDCONTAINER_H
#define HAZARDCONTAINER_H

#include <vector>

#include "CommonFuncs.h"
#include "GameEnums.h"
#include "Hazard.h"

using namespace std;


class HazardContainer {
private:
	vector<Hazard*> hazards;

public:
	// constructors and destructors
	HazardContainer();
	~HazardContainer();

	// accessor methods
	Hazard* getHazard(int ID);
	Hazard* getHazard(string hazardName);
	Hazard* getLastHazard();
	int getNumHazards();
	int getNumRoamingHazards();

	vector<Hazard*>* getHazardsVector();

	// mutator methods
	void addHazard(Hazard* hazard);
	void removeHazard(int ID);

};



#endif