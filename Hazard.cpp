/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Hazard Class Definition File

The Definition file for the Hazard class which 
serves as the base class for the game's hazards and 
opponents.

**************************************************/

#include "Hazard.h"

int Hazard::numHazards = 0;

//-------------------------------------//
// static accessors                    //
//-------------------------------------//

int Hazard::getNumHazards() {
	return numHazards;
}



//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Hazard::Hazard() {
	numHazards++;

	hazardID = -1;
	hazardName = "";
	hazardType = NOHAZARD;
	currentRoom = 0;
	hazardHint = "";

	eventDescriptions = {};

	isRoamingType = false;
	isLivingType = false;
	isDead = false;
}


Hazard::Hazard(string name, HazardType type, string hint, vector<string> descriptions, bool roaming, bool living) {
	numHazards++;

	hazardID = numHazards;
	hazardName = name;
	hazardType = type;
	currentRoom = 0;
	hazardHint = hint;

	eventDescriptions = descriptions;

	isRoamingType = roaming;
	isLivingType = living;
	isDead = false;
}


Hazard::~Hazard() {
	--numHazards;
}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//
int Hazard::getID() {
	return hazardID;
}


string Hazard::getName() {
	return hazardName;
}


HazardType Hazard::getType() {
	return hazardType;
}


string Hazard::getTypeAsString() {
	switch (getType()) {
		case ARIGAMO:
			return "Arigamo";

		case PIT:
			return "Bottomless Pit";

		case CCRAT:
			return "Colony of Corrupted Rats";

		case ORACLE:
			return "Corrupted Oracle";

		case THIEF:
			return "Opportunistic Thief";

		case RAIDERS:
			return "Outcasted Raiders";

		case TRADER:
			return "Suspicious Trader";

		case KNIGHT:
			return "Dark Knight";

		default:
			return "No type has been assigned";
	}
}


int Hazard::getCurrentRoom() {
	return currentRoom;
}


string Hazard::getHint() {
	return hazardHint;
}


vector<string> Hazard::getEventDescriptions() {
	return eventDescriptions;
}


string Hazard::getDescriptionsAsString() {
	// returns contents of eventDescriptions as string
	// adapted from Week 7 Lab notes

	string descriptions = "";

	if (!eventDescriptions.empty()) {
		vector<string>::const_iterator iter;

		for (iter = eventDescriptions.begin(); iter != eventDescriptions.end(); iter++) {
			string line = *iter;
			descriptions += line + ", ";
		}
	}
	else {
		descriptions = "There are no descriptions for the Hazard";
	}

	return descriptions;
}

bool Hazard::hasGem() {
	if (fuhaiGem.getType() != NOITEM) {
		return true;
	}
	else {
		return false;
	}
}

bool Hazard::isRoaming() {
	return isRoamingType;
}


bool Hazard::IsLiving() {
	return isLivingType;
}


bool Hazard::hasDied() {
	return isDead;
}


string Hazard::getDetails() {
	// returns details of the hazard as formatted string

	stringstream hazardDetails;

	hazardDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	hazardDetails << " Hazard ID: " << getID() << "\n";
	hazardDetails << " Hazard Name: " << getName() << "\n";
	hazardDetails << " Hazard Type: " << getTypeAsString() << "\n";
	hazardDetails << " Current Room: " << getCurrentRoom() << "\n";
	hazardDetails << " Hint: " << getHint() << "\n";
	hazardDetails << " Event Descriptions: " << getDescriptionsAsString() << "\n";
	hazardDetails << " Is Roaming Type: " << isRoaming() << "\n";
	hazardDetails << " Is Living Type: " << IsLiving() << "\n";
	hazardDetails << " Is Dead: " << hasDied() << "\n";
	hazardDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return hazardDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void Hazard::setID(int ID) {
	if (ID >= 0) {
		hazardID = ID;

	}
	else {
		cout << " You have not entered a valid hazard ID to set.\n";
	}
}

void Hazard::setName(string name) {
	if (name.find_first_not_of(' ') != string::npos) {
		hazardName = name;

	}
	else {
		cout << " You have not entered a valid hazard name to set.\n";
	}
}


void Hazard::setType(HazardType type) {
	if (type != NULL) {
		hazardType = type;

	}
	else {
		cout << " You have not entered a valid hazard type to set.\n";
	}
}


void Hazard::setStartingRoom(vector<Room*>& world, int room) {
	// sets the hazard's starting room

	if (room >= 0) {
		currentRoom = room;
		world[room]->addHazard(hazardID);

	}
	else {
		cout << " You have not entered a starting room to set.\n";
	}
}


void Hazard::setCurrentRoom(int room) {
	if (room >= 0) {
		currentRoom = room;

	}
	else {
		cout << " You have not entered a valid current room number to set.\n";
	}
}


void Hazard::setHint(string hint) {
	if (hint.find_first_not_of(' ') != string::npos) {
		hazardHint = hint;

	}
	else {
		cout << " You have not entered a valid hazard hint to set.\n";
	}
}


void Hazard::setRoamingType(bool isRoaming) {
	isRoamingType = isRoaming;
}


void Hazard::setLivingType(bool living) {
	isLivingType = living;
}


void Hazard::setIsDead(bool dead) {
	isDead = dead;
}


void Hazard::setEventDescriptions(vector<string> events) {
	if (!events.empty()) {
		eventDescriptions = events;
	}
	else {
		cout << " You have not entered a valid hazard description vector to set.\n";
	}
}


void Hazard::setGem(Item gem) {
	if (gem.getType() != MAGIC) {
		fuhaiGem = gem;

	}
	else {
		cout << " You have not given a valid gem.\n";
	}
}

void Hazard::kill() {
	// kills the hazard

	isDead = true;
}



//-------------------------------------//
// movement methods                    //
//-------------------------------------//

void Hazard::moveTo(vector<Room*>& world, int room) {
	// moves the hazard into the desired room updates the appropriate rooms

	world[currentRoom]->removeHazard(hazardID);
	setCurrentRoom(room);
	world[room]->addHazard(hazardID);
}


vector<string> Hazard::updateInteraction() {
	vector<string> updateDescriptions = {"There are no interactions."};
	return updateDescriptions;
}


void Hazard::roomInteraction() {
	if (isDead) {
		cout << "\n" << eventDescriptions[3] << "\n";
	}
	else {
		cout << "\n There is nothing in the Room to interact with.";
	}
}
