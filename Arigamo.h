/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Arigamo Class Header File

The Header file for the Arigamo class - the main
objective of the game.

**************************************************/

#ifndef ARIGAMO_H
#define ARIGAMO_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>

#include "GameEnums.h"
#include "Hazard.h"
#include "Item.h"
#include "Player.h"

using namespace std;


class Arigamo : public Hazard {
private:
	int healthDrainRate;

	bool isAsleep;

	int turnsToWake;
	float baseRoamChance;
	float roamChanceMod;

	bool canDrainPlayer(int* roomConnections, int total_rooms, int playerRoom);
	vector<int> neighbours(int* roomConnections, int total_rooms, int room);
	int calculateRoamChance(int entitiesAlive);

public:
	// constructors and destructors 
	Arigamo();
	Arigamo(string name, HazardType type, string hint, vector<string> description, bool roaming, bool conscious, int hpDrain, float baseRoam);
	~Arigamo();

	// accessor methods
	int getHealthDrainRate();
	bool isSleeping();
	int getTurnsToWake();
	float getBaseRoamChance();
	float getRoamChanceMod();
	string getDetails();

	// mutator methods
	void setHealthDrainRate(int rate);
	void setIsAsleep(bool asleep);
	void setTurnsToWake(int turns);
	void setBaseRoamChance(float chance);
	void setRoamChanceMod(float chance);
	void updateTurnsToWake(int turns);

	// hazard turn update methods
	void wakeArigamo(int entitiesAlive);
	void resetTurnsToWake();
	vector<string> drainPlayerHP(int* roomConnections, int total_rooms, Player & player);
	Item giveGem();

	vector<string> updateInteraction(Hazard* hazard);
	vector<string> updateInteraction(Player& player);
};



#endif