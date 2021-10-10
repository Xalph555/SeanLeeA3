/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Outcasted Raiders Class Definition File

The Definition file for the Outcasted Raiders class Hazard.

**************************************************/

#include "Raiders.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Raiders::Raiders() {
	damageAmount = 0;
}


Raiders::Raiders(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious, int damage) : Hazard(name, type, hint, description, roaming, conscious) {
	damageAmount = damage;
}


Raiders::~Raiders() {

}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

int Raiders::getDamageAmount() {
	return damageAmount;
}


string Raiders::getDetails() {
	// returns details of the raiders as formatted string

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
	hazardDetails << " Has Interacted: " << interacted() << "\n";
	hazardDetails << " Damage: " << getDamageAmount() << "\n";
	hazardDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return hazardDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void Raiders::setDamageAmount(int damage) {
	if (damage > 0) {
		damageAmount = damage;

	}
	else {
		displayString(" You have not entered a valid amount of damage to set.\n");
	}
}



//-------------------------------------//
// hazard turn update methods          //
//-------------------------------------//

vector<string> Raiders::updateInteraction(Player& player, RoomContainer& world) {
	// the raiders interaction with the player

	vector<string> results;

	setHasInteracted(true);

	if (!hasDied()) {
		vector<int> availableExits = world.getRoom(getCurrentRoom())->getExitConnections();

		int randomRoom = availableExits[rand() % availableExits.size()];
		player.moveTo(world, randomRoom, true);

		player.updateHealth(-damageAmount);

		results.push_back(eventDescriptions[0]);
		results.push_back(eventDescriptions[1]);

		if (player.getHealthCurrent() == 0) {
			results.push_back("$");
		}

	}
	else {
		results.push_back(eventDescriptions[3]);
	}

	return results;
}

