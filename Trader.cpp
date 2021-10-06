/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Suspicious Trader Class Definition File

The Definition file for the Suspicious Trader class Hazard.

**************************************************/

#include "Trader.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Trader::Trader() {
}


Trader::Trader(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious) : Hazard(name, type, hint, description, roaming, conscious) {
}


Trader::~Trader() {
}



//-------------------------------------//
// hazard turn update methods          //
//-------------------------------------//

vector<string> Trader::updateInteraction(Player& player, vector<Room*>& world) {
	// the thief's interaction with the player

	vector<string> results;

	if (!hasDied()) {
		// "Trade" with player
		vector<int> choices;

		if (player.getItem("Crossbow Bolts")->getAmount() > 1) {
			choices.push_back(1);
		}

		if (player.getItem("Incense Sticks")->getAmount() > 2) {
			choices.push_back(2);
		}

		if (!choices.empty()) {
			int choice = choices[rand() % choices.size()];
			switch (choice) {
			case 1:
				player.getItem("Crossbow Bolts")->updateAmount(-1);
				player.getItem("Incense Sticks")->updateAmount(2);
				break;

			case 2:
				player.getItem("Incense Sticks")->updateAmount(-3);
				player.getItem("Crossbow Bolts")->updateAmount(1);
				break;
			}
		}

		results.push_back(eventDescriptions[0]);
		results.push_back(eventDescriptions[1]);

	}
	else {
		results.push_back(eventDescriptions[3]);
	}

	return results;
}

