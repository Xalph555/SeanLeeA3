/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Dark Knight Class Definition File

The Definition file for the Dark Knight class Hazard.

**************************************************/

#include "Knight.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Knight::Knight() {
	damageAmount = 0;

}


Knight::Knight(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious, int damage) : Hazard(name, type, hint, description, roaming, conscious) {
	damageAmount = damage;

}


Knight::~Knight() {
}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

int Knight::getDamageAmount() {
	return damageAmount;
}


string Knight::getDetails() {
	// returns details of the knight as formatted string

	stringstream hazardDetails;

	hazardDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	hazardDetails << " Hazard ID: " << getID() << "\n";
	hazardDetails << " Hazard Name: " << getName() << "\n";
	hazardDetails << " Hazard Type: " << getTypeAsString() << "\n";
	hazardDetails << " Current Room: " << getCurrentRoom() << "\n";
	hazardDetails << " Hint: " << getHint() << "\n";
	hazardDetails << " Event Descriptions: " << getDescriptionsAsString() << "\n";
	hazardDetails << " Is Roaming Type: " << isRoaming() << "\n";
	hazardDetails << " Is Conscious: " << conscious() << "\n";
	hazardDetails << " Is Dead: " << hasDied() << "\n";
	hazardDetails << " Damage: " << getDamageAmount() << "\n";
	hazardDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return hazardDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void Knight::setDamageAmount(int damage) {
	if (damage > 0) {
		damageAmount = damage;

	}
	else {
		cout << " You have not entered a valid amount of damage to set.\n";
	}
}


//-------------------------------------//
// hazard turn update methods          //
//-------------------------------------//

vector<string> Knight::updateInteraction(Player& player) {
	// the Dark Knight's interaction with the player

	vector<string> results;

	if (!hasDied()) {
		if (conscious()) {
			player.updateHealth(-damageAmount);
			setIsConscious(false);

			results.push_back(eventDescriptions[0]);
			results.push_back(eventDescriptions[1]);

		}
		else {
			results.push_back(eventDescriptions[4]);
		}

	}
	else {
		results.push_back(eventDescriptions[3]);
	}

	return results;
}