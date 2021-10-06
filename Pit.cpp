/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Bottomless Pit Class Definition File

The Definition file for the Bottomless Pit class Hazard.

**************************************************/


#include "Pit.h"

//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Pit::Pit() {
}


Pit::Pit(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious) : Hazard(name, type, hint, description, roaming, conscious) {
}


Pit::~Pit() {
}




//-------------------------------------//
// hazard turn update methods          //
//-------------------------------------//

vector<string> Pit::updateInteraction(Player& player) {
	// the bottomless pit's interaction with the player

	vector<string> results;

	player.kill();

	results.push_back(eventDescriptions[0]);
	results.push_back(eventDescriptions[1]);

	return results;
}

