/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Opportunistic Thief Class Definition File

The Definition file for the Opportunistic Thief class Hazard.

**************************************************/

#include "Thief.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Thief::Thief() {
}


Thief::Thief(string name, HazardType type, string hint, vector<string> description, bool roaming, bool living) : Hazard(name, type, hint, description, roaming, living) {
}


Thief::~Thief() {
}



//-------------------------------------//
// hazard turn update methods          //
//-------------------------------------//

vector<string> Thief::updateInteraction(Player& player, vector<Room*>& world) {
	// the thief's interaction with the player

	vector<string> results;

	// steal item from player
	vector<int> choices;

	if (player.getItem("Crossbow Bolts")->getAmount() > 1) {
		choices.push_back(1);
	}

	if (player.getItem("Incense Sticks")->getAmount() > 2) {
		choices.push_back(2);
	}

	if (player.getItem("Telecard")->getAmount() > 0) {
		choices.push_back(3);
	}

	if (!choices.empty()) {
		int choice = choices[rand() % choices.size()];
		switch (choice) {
			case 1:
				player.getItem("Crossbow Bolts")->updateAmount(-1);
				break;

			case 2:
				player.getItem("Incense Sticks")->updateAmount(-2);
				break;

			case 3:
				player.getItem("Telecard")->updateAmount(-1);
				break;
		}
	}

	// return event results
	results.push_back(eventDescriptions[0]);
	results.push_back(eventDescriptions[1]);

	return results;
}

