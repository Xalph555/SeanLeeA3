/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Corrupted Oracle Class Definition File

The Definition file for the Corrupted Oracle class Hazard.

**************************************************/

#include "Oracle.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Oracle::Oracle() {
	hasInteracted = false;
}


Oracle::Oracle(string name, HazardType type, string hint, vector<string> description, bool roaming, bool living) : Hazard(name, type, hint, description, roaming, living) {
	hasInteracted = false;
}


Oracle::~Oracle() {
}

//-------------------------------------//
// accessor methods                    //
//-------------------------------------//
bool Oracle::getHasInteracted() {
	return hasInteracted;
}


string Oracle::getDetails() {
	// returns details of the Oracle as formatted string

	stringstream oracleDetails;

	oracleDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	oracleDetails << " Hazard ID: " << getID() << "\n";
	oracleDetails << " Hazard Name: " << getName() << "\n";
	oracleDetails << " Hazard Type: " << getTypeAsString() << "\n";
	oracleDetails << " Current Room: " << getCurrentRoom() << "\n";
	oracleDetails << " Hint: " << getHint() << "\n";
	oracleDetails << " Event Descriptions: " << getDescriptionsAsString() << "\n";
	oracleDetails << " Is Roaming Type: " << isRoaming() << "\n";
	oracleDetails << " Is Living Type: " << IsLiving() << "\n";
	oracleDetails << " Is Dead: " << hasDied() << "\n";
	oracleDetails << " Damage: " << getHasInteracted() << "\n";
	oracleDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return oracleDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//
void Oracle::setHasInteracted(bool interacted) {
	hasInteracted = interacted;
}



//-------------------------------------//
// hazard turn update methods          //
//-------------------------------------//

vector<string> Oracle::updateInteraction(Player& player) {
	// the Oracle's interaction with the player

	vector<string> results;

	results.push_back(eventDescriptions[0]);
	results.push_back(eventDescriptions[1]);

	return results;
}


void Oracle::roomInteraction(Player& player, int arigamoRoom) {
	// interaction with the player through player's INTERACT action

	if (!hasInteracted) {
		hasInteracted = true;

		bool userInput = false;

		cout << "\n Hello beast tamer. I sense great guilt within you.\n";
		cout << " I presume you wish to find the Arigamo? The one you brought into this world?\n";
		cout << " I can tell you where it is... For a price.\n";

		userInput = getBoolInput(" Trade 1/3 of your 'Crossbow Bolts' and 1/2 of your 'Incense Sticks'\n to reveal the Arigamo's location? (Y/N): ");

		if (userInput) {
			player.getItem("Crossbow Bolts")->updateAmount(floor(player.getItem("Crossbow Bolts")->getAmount() / 3));
			player.getItem("Incense Sticks")->updateAmount(floor(player.getItem("Incense Sticks")->getAmount() / 2));

			cout << "\n (The trade was made)\n";
			cout << " Thank you. You can find the Arigamo in room " << arigamoRoom << ".\n";
			cout << " I wish you all the best on your journey... beast tamer.\n";

		}
		else {
			cout << " I see. I wish you all the best on your journey... beast tamer.\n";
		}

	}
	else {
		cout << "\n" << eventDescriptions[4] << "\n";
	}
}