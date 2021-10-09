/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Colony of Corrupted Rats Class Header File

The Header file for the CCRats class Hazard.

**************************************************/


#include "CCRats.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

CCRats::CCRats() {
	damageAmount = 0;

}


CCRats::CCRats(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious, int damage) : Hazard(name, type, hint, description, roaming, conscious) {
	damageAmount = damage;

}


CCRats::~CCRats() {

}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

int CCRats::getDamageAmount() {
	return damageAmount;
}


string CCRats::getDetails() {
	// returns details of the CCRats as formatted string

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

void CCRats::setDamageAmount(int damage) {
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

vector<string> CCRats::updateInteraction(Player& player, RoomContainer& world) {
	// the ccRats interaction with the player

	vector<string> results;

	int randomRoom = rand() % world.getNumRooms();
	player.moveTo(world, randomRoom, true);


	//player.moveTo(world, 19, true);

	player.updateHealth(-damageAmount);
	setHasInteracted(true);

	results.push_back(eventDescriptions[0]);
	results.push_back(eventDescriptions[1]);

	if (player.getHealthCurrent() == 0) {
		results.push_back("$");
	}

	return results;
}