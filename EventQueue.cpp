/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Event Queue Class Definition File

The Definition file for the Event Queue class which
holds the description for the game's events after
each turn.

**************************************************/

#include "EventQueue.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

EventQueue::EventQueue() {
	eventDescriptions = {};
}


EventQueue::~EventQueue() {
}




//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

vector<string> EventQueue::getEventQueueContents() {
	return eventDescriptions;
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void EventQueue::updateEventQueue(vector<string> events) {
	// adds the input events vector to the event queue

	if (!events.empty()) {
		eventDescriptions.insert(eventDescriptions.end(), events.begin(), events.end());

	}
	else {
		cout << " You have not entered a valid event string vector to add to the event queue.\n";
	}
}


void EventQueue::updateEventQueue(string events) {
	// adds the input event to the event queue

	if (events.find_first_not_of(' ') == string::npos) {
		eventDescriptions.push_back(events);

	}
	else {
		cout << " You have not entered a valid event string to add to the event queue.\n";
	}
}


void EventQueue::clearEventQueue() {
	eventDescriptions.clear();
}