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


Raiders::Raiders(string name, HazardType type, string hint, vector<string> description, bool roaming, bool living, int damage) : Hazard(name, type, hint, description, roaming, living) {
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

	stringstream raidersDetails;

	raidersDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	raidersDetails << " Hazard ID: " << getID() << "\n";
	raidersDetails << " Hazard Name: " << getName() << "\n";
	raidersDetails << " Hazard Type: " << getTypeAsString() << "\n";
	raidersDetails << " Current Room: " << getCurrentRoom() << "\n";
	raidersDetails << " Hint: " << getHint() << "\n";
	raidersDetails << " Event Descriptions: " << getDescriptionsAsString() << "\n";
	raidersDetails << " Is Roaming Type: " << isRoaming() << "\n";
	raidersDetails << " Is Living Type: " << IsLiving() << "\n";
	raidersDetails << " Is Dead: " << hasDied() << "\n";
	raidersDetails << " Damage: " << getDamageAmount() << "\n";
	raidersDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return raidersDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void Raiders::setDamageAmount(int damage) {
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

vector<string> Raiders::updateInteraction(Player& player, vector<Room*>& world) {
	// the raiders interaction with the player

	vector<string> results;

	vector<int> availableExits = world[getCurrentRoom()]->getExitConnections();

	int randomRoom = availableExits[rand() % availableExits.size()];
	player.moveTo(world, randomRoom, true);

	player.updateHealth(-damageAmount);

	results.push_back(eventDescriptions[0]);
	results.push_back(eventDescriptions[1]);

	return results;
}

