/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Arigamo Class Definition File

The Definition file for the Arigamo class - the main
objective of the game.

**************************************************/

#include "Arigamo.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Arigamo::Arigamo() {
	healthDrainRate = 0;

	fuhaiGem = Item();
	isAsleep = true;

	turnsToWake = 0;
	baseRoamChance = 0.0;
	roamChanceMod = 0.0;
}


Arigamo::Arigamo(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious, int hpDrain, float baseRoam) : Hazard(name, type, hint, description, roaming, conscious) {
	healthDrainRate = hpDrain;

	fuhaiGem = Item("Fuhai Gem", MAGIC, 1);
	isAsleep = true;

	turnsToWake = rand() % 6 + 3;
	baseRoamChance = baseRoam;
	roamChanceMod = 0.4;
}


Arigamo::~Arigamo() {

}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

int Arigamo::getHealthDrainRate() {
	return healthDrainRate;
}


bool Arigamo::isSleeping() {
	return isAsleep;
}


int Arigamo::getTurnsToWake() {
	return turnsToWake;
}


float Arigamo::getBaseRoamChance() {
	return baseRoamChance;
}


float Arigamo::getRoamChanceMod() {
	return roamChanceMod;
}


string Arigamo::getDetails() {
	// returns details of the Arigamo as formatted string

	stringstream hazardDetails;

	hazardDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	hazardDetails << " Arigamo ID: " << getID() << "\n";
	hazardDetails << " Arigamo Name: " << getName() << "\n";
	hazardDetails << " Arigamo Type: " << getTypeAsString() << "\n";
	hazardDetails << " Current Room: " << getCurrentRoom() << "\n";
	hazardDetails << " Hint: " << getHint() << "\n";
	hazardDetails << " Event Descriptions: " << getDescriptionsAsString() << "\n";
	hazardDetails << " Is Roaming Type: " << isRoaming() << "\n";
	hazardDetails << " Is Conscious: " << conscious() << "\n";
	hazardDetails << " Is Dead: " << hasDied() << "\n";
	hazardDetails << " Has Interacted: " << interacted() << "\n";
	hazardDetails << " Health Drain Rate: " << getHealthDrainRate() << "\n";
	hazardDetails << " Has Gem: " << hasGem() << "\n";
	hazardDetails << " Is Asleep: " << isSleeping() << "\n";
	hazardDetails << " Turns till Wake: " << getTurnsToWake() << "\n";
	hazardDetails << " Base Roam Chance: " << getBaseRoamChance() << "\n";
	hazardDetails << " Roam Chance Modifier: " << getRoamChanceMod() << "\n";
	hazardDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return hazardDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void Arigamo::setHealthDrainRate(int rate) {
	if (rate > 0) {
		healthDrainRate = rate;

	}
	else {
		displayString(" You have not entered a valid health drain rate to set.\n");
	}
}


void Arigamo::setIsAsleep(bool asleep) {
	isAsleep = asleep;
}


void Arigamo::setTurnsToWake(int turns) {
	if (turns >= 0) {
		turnsToWake = turns;

	}
	else {
		displayString(" You have not entered a valid number of turns to set.\n");
	}
}


void Arigamo::setBaseRoamChance(float chance) {
	if (chance >= 0.0 || chance < 1.0) {
		baseRoamChance = chance;

	}
	else {
		displayString(" You have not entered a valid base roam chance to set.\n");
	}
}


void Arigamo::setRoamChanceMod(float chance) {
	if (chance >= 0.0 || chance < 1.0) {
		roamChanceMod = chance;

	}
	else {
		displayString(" You have not entered a valid roam chance modifier to set.\n");
	}
}


void Arigamo::updateTurnsToWake(int turns) {
	if (turns != 0) {
		turnsToWake += turns;

		if (turnsToWake <= 0) {
			turnsToWake = 0;
		}

	}
	else {
		displayString(" You have not entered a valid number of turns to update turnsToWake set.\n");
	}
}



//-------------------------------------//
// hazard turn update methods          //
//-------------------------------------//

int Arigamo::calculateRoamChance(int entitiesAlive) {
	// the chance of the Arigamo roaming increases as the 
	// number of alive roaming opponents decrease
	int roamChance = (baseRoamChance + (roamChanceMod / entitiesAlive)) * 100;
	return roamChance;
}


void Arigamo::wakeArigamo(int entitiesAlive) {
	// check to see if arigamo can be woken up

	if (isSleeping() && turnsToWake == 0) {
		int wakeUp = rand() % (100 - calculateRoamChance(entitiesAlive));

		if (wakeUp == 0) {
			setIsAsleep(false);

		}
	}
}


void Arigamo::resetTurnsToWake() {
	turnsToWake = rand() % 6 + 3;
}


vector<string> Arigamo::drainPlayerHP(int* roomConnections, int total_rooms, Player& player) {
	// drains the health of the player of they are close enough
	// Madan, S. (2020). Passing a 2D Array as a Function Parameter in C and C++. Retrieved from https://medium.com/swlh/passing-a-2-d-array-as-a-function-parameter-in-c-mainly-c-7a29d196530a

	vector<string> results;

	if (canDrainPlayer(roomConnections, total_rooms, player.getCurrentRoom())) {
		player.updateHealth(-healthDrainRate);
		results.push_back(eventDescriptions[5]);
		
		if (player.getHealthCurrent() == 0) {
			results.push_back(" Your life has been completely drained.");
			results.push_back("$");
		}
	}

	return results;
}


bool Arigamo::canDrainPlayer(int* roomConnections, int total_rooms, int playerRoom) {
	// checks whether the player is close enough to the Arigamo to be drained

	if (!hasDied()) {
		vector<int> dists(total_rooms, 0);
		dists[currentRoom] = 0;

		vector<int> visited;
		deque<int> boundary;
		boundary.push_back(currentRoom);

		while (boundary.size() > 0) {
			int v = boundary.front();
			boundary.pop_front();
			visited.push_back(v);

			vector<int> nextCons = neighbours(roomConnections, total_rooms, v);

			vector<int>::const_iterator iter;
			for (iter = nextCons.begin(); iter != nextCons.end(); iter++) {
				int u = *iter;

				if (find(visited.begin(), visited.end(), u) == visited.end() && find(boundary.begin(), boundary.end(), u) == boundary.end()) {
					boundary.push_back(u);
					dists[u] += dists[v] + 1;

					if (u == playerRoom && dists[u] < 3) {
						return true;
					}
				}

			}
		}
	}

	return false;
}


vector<int> Arigamo::neighbours(int* roomConnections, int total_rooms, int room) {
	vector<int> res;

	for (int i = 0; i < total_rooms; i++) {
		if (*((roomConnections + room * total_rooms) + i) == 1) {
			res.push_back(i);
		}
	}

	return res;
}


Item Arigamo::giveGem() {
	// returns and removes the Fuhai gem from the Arigamo

	Item gemTemp = fuhaiGem;
	fuhaiGem = Item();

	return gemTemp;
}


vector<string> Arigamo::updateInteraction(Hazard* hazard) {
	// the arigamo's interaction with a hazard

	vector<string> results;

	if (!hasDied()) {
		if (!hazard->hasDied() && hazard->isRoaming()) {
			hazard->kill();

			results.push_back(hazard->getEventDescriptions()[2]);

		}
	}
	else {
		if (hasGem() && !hazard->hasDied() && hazard->isRoaming()) {
			hazard->setGem(giveGem());
		}
	}

	return results;
}


vector<string> Arigamo::updateInteraction(Player& player) {
	// the arigamo's interaction with the player

	vector<string> results;

	setHasInteracted(true);

	if (!hasDied()) {
		player.kill();

		results.push_back(eventDescriptions[0]);
		results.push_back(eventDescriptions[1]);
		results.push_back("$");
	}
	else {
		results.push_back(eventDescriptions[3]);

		if (hasGem()) {
			player.updateInventory(giveGem());

			results.push_back(" You have retreived the Fuhai Gem!\n");
			results.push_back("$");

		}
		else {
			results.push_back(" The Fuhai Gem was nowhere to be found...\n");
			results.push_back("$");
		}
	}

	return results;
}
