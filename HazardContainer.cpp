/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Hazard Container Class Definition File

The Definition file for the Hazard Container class which
serves as a custom container for the game's hazards.

**************************************************/

#include "HazardContainer.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

HazardContainer::HazardContainer() {
	hazards = {};
}


HazardContainer::~HazardContainer() {
	// removing pointers from heap

	for (int i = hazards.size() - 1; i >= 0; --i) {
		delete hazards[i];
		hazards[i] = nullptr;
	}
}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

Hazard* HazardContainer::getHazard(int ID) {
	// finds and returns the pointer to the hazard from the hazard collection based on the given hazardID

	vector<Hazard*>::const_iterator iter;

	for (iter = hazards.begin(); iter != hazards.end(); iter++) {
		if ((*iter)->getID() == ID) {
			return &(**iter);
		}
	}

	return nullptr;
}


Hazard* HazardContainer::getHazard(string hazardName) {
	// finds and returns the pointer to the hazard from the hazard collection based on the given hazardName

	vector<Hazard*>::const_iterator iter;

	for (iter = hazards.begin(); iter != hazards.end(); iter++) {
		if ((*iter)->getName() == hazardName){
			return &(**iter);
		}
	}

	return nullptr;
}


Hazard* HazardContainer::getLastHazard() {
	// returns the last hazard added to the hazards collection

	return hazards[hazards.size() - 1];
}


int HazardContainer::getNumHazards() {
	return hazards.size();
}


int HazardContainer::getNumRoamingHazards() {
	// returns the number of roaming hazards that are still alive

	int alive = 0;

	vector<Hazard*>::const_iterator iter;

	for (iter = hazards.begin(); iter != hazards.end(); iter++) {
		if ((*iter)->isRoaming() && !(*iter)->hasDied() && (*iter)->getType() != ARIGAMO) {
			alive++;
		}
	}

	return alive;
}


string HazardContainer::getAllHazardInfo(){
	// returns the name, room number, and death status of all hazards in the container
	
	stringstream hazardInfo;

	hazardInfo << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	vector<Hazard*>::const_iterator iter;
	for (iter = hazards.begin(); iter != hazards.end(); iter++) {
		Hazard* haz = *iter;

		hazardInfo << " Name: " << haz->getName() << ", Type: " << haz->getTypeAsString() << ", Room: " << haz->getCurrentRoom() << "\n";
	}

	hazardInfo << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return hazardInfo.str();
}


vector<Hazard*>* HazardContainer::getHazardsVector() {
	return &hazards;
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void HazardContainer::addHazard(Hazard* hazard) {
	// adds the input hazard to the hazard collection

	if (hazard != nullptr) {
		hazards.push_back(hazard);

	}
	else {
		displayString(" You have not entered a valid hazard to add to the container.\n");
	}
}


void HazardContainer::removeHazard(int ID) {
	// removes a specific hazard based on the give hazardID

	vector<Hazard*>::iterator iter;

	for (iter = hazards.begin(); iter != hazards.end(); iter++) {
		if ((*iter)->getID() == ID) {
			delete (*iter);
			*iter = nullptr;
			hazards.erase(iter);

			break;
		}
	}

	displayString(" You have not entered a valid hazard ID to remove from the container.\n");
}