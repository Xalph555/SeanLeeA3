/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Event Queue Class Header File

The Header file for the Event Queue class which
holds the description for the game's events after
each turn.

**************************************************/

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <vector>
#include <string>

#include "CommonFuncs.h"
#include "GameEnums.h"

using namespace std;


class EventQueue {
private:
	vector<string> eventDescriptions;

public:
	// constructors and destructors
	EventQueue();
	~EventQueue();

	// accessor methods
	vector<string> getEventQueueContents();

	// mutator methods
	void updateEventQueue(vector<string> events);
	void updateEventQueue(string events);

	void clearEventQueue();
};



#endif