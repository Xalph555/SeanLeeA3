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


CCRats::CCRats(string name, HazardType type, string hint, vector<string> description, bool roaming, bool living, int damage) : Hazard(name, type, hint, description, roaming, living) {
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

	stringstream ccRatsDetails;

	ccRatsDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	ccRatsDetails << " Hazard ID: " << getID() << "\n";
	ccRatsDetails << " Hazard Name: " << getName() << "\n";
	ccRatsDetails << " Hazard Type: " << getTypeAsString() << "\n";
	ccRatsDetails << " Current Room: " << getCurrentRoom() << "\n";
	ccRatsDetails << " Hint: " << getHint() << "\n";
	ccRatsDetails << " Event Descriptions: " << getDescriptionsAsString() << "\n";
	ccRatsDetails << " Is Roaming Type: " << isRoaming() << "\n";
	ccRatsDetails << " Is Living Type: " << IsLiving() << "\n";
	ccRatsDetails << " Is Dead: " << hasDied() << "\n";
	ccRatsDetails << " Damage: " << getDamageAmount() << "\n";
	ccRatsDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return ccRatsDetails.str();
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

vector<string> CCRats::updateInteraction(Player& player, vector<Room*>& world) {
	// the ccRats interaction with the player

	vector<string> results;

	int randomRoom = rand() % world.size();
	player.moveTo(world, randomRoom, true);

	player.updateHealth(-damageAmount);

	results.push_back(eventDescriptions[0]);
	results.push_back(eventDescriptions[1]);

	return results;
}

