/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Room Class Definition File

The Definition file for the Room class which contains
the attributes and behaviours of the locations
in the Abandoned Ruins.

**************************************************/

#include "Room.h"


//-------------------------------------//
// constructors and destructors        //
//-------------------------------------//

Room::Room() {
	roomNumber = 0;
	roomName = "";
	roomDescription = "";
	roomExitDirections = {};
	roomExitConnections = {};

	hasPlayer = false;
	hazards = {};
}


Room::Room(int num, string name, string description, vector<string> exitDir, vector<int> exitConnections) {
	roomNumber = num;
	roomName = name;
	roomDescription = description;
	roomExitDirections = exitDir;
	roomExitConnections = exitConnections;

	hasPlayer = false;
	hazards = {};
}


Room::~Room() {
}



//-------------------------------------//
// accessor methods                    //
//-------------------------------------//

int Room::getNumber() {
	return roomNumber;
}


string Room::getName() {
	return roomName;
}


string Room::getDescription() {
	return roomDescription;
}


vector<string> Room::getExitDirections() {
	return roomExitDirections;
}


string Room::getExitDirectionsAsString() {
	// returns contents of roomExitDirections as a string
	// adapted from Week 7 Lab notes

	string directions = "";

	if (!roomExitDirections.empty()) {
		vector<string>::const_iterator iter;

		for (iter = roomExitDirections.begin(); iter != roomExitDirections.end(); iter++) {
			string dir = *iter;
			directions += dir + ", ";
		}
	}
	else {
		directions = "There are no exit directions.";
	}

	return directions;
}


vector<int> Room::getExitConnections() {
	return roomExitConnections;
}


string Room::getExitConnectionsAsString() {
	// returns contents of roomExitConnections as a string
	// adapted from Week 7 Lab notes

	string connections = "";

	if (!roomExitConnections.empty()) {
		vector<int>::const_iterator iter;

		for (iter = roomExitConnections.begin(); iter != roomExitConnections.end(); iter++) {
			int con = *iter;
			connections += to_string(con) + ", ";
		}
	}
	else {
		connections = "There are no exit connections.";
	}

	return connections;
}


int Room::getRoomConnection(string direction) {
	// returns the room number associated with the input direction
	// if the direction is not valid, return -1

	if (!roomExitDirections.empty()) {

		for (int i = 0; i < roomExitDirections.size(); i++) {

			if (roomExitDirections[i] == direction){
				return roomExitConnections[i];
			}
		}
	}
	
	return -1;
}


bool Room::isPlayerInRoom() {
	return hasPlayer;
}


vector<int> Room::getHazards(){
	return hazards;
}


string Room::getHazardsAsString(){
	// returns the hazard IDs within the room as a string
	// adapted from Week 7 Lab notes

	string hazardsInRoom = "";

	if (!hazards.empty()) {
		vector<int>::const_iterator iter;

		for (iter = hazards.begin(); iter != hazards.end(); iter++) {
			int hazard = *iter;
			hazardsInRoom += to_string(hazard) + ", ";
		}
	}
	else {
		hazardsInRoom = "There are no hazards.";
	}

	return hazardsInRoom;
}


bool Room::hasHazard(){
	return !hazards.empty();
}


string Room::getRoomInfo() {
	// returns the room's description/ game information

	stringstream info;

	info << " [" << getNumber() << "] " << getName() << "\n";
	info << getDescription();

	return info.str();
}


string Room::getRoomExits() {
	// returns the room's exit directions and the rooms they lead to

	stringstream exits;

	if (!roomExitConnections.empty()) {
		exits << " Avaliable exits: ";

		unsigned int i = 0;
		for (i; i < roomExitConnections.size() - 1; i++) {
			exits << roomExitDirections[i] << "(" << roomExitConnections[i] << "), ";

		}

		exits << roomExitDirections[i] << "(" << roomExitConnections[i] << ")\n";
	}
	else {
		exits << " There are no exit connections\n";
	}

	return exits.str();
}


string Room::getDetails() {
	// returns the class details of room as formatted string

	stringstream roomDetails;

	roomDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	roomDetails << " Room Number: " << getNumber() << "\n";
	roomDetails << " Room Name: " << getName() << "\n";
	roomDetails << " Room Description: " << getDescription() << "\n";
	roomDetails << " Exit Directions: " << getExitDirectionsAsString() << "\n";
	roomDetails << " Exit Connections: " << getExitConnectionsAsString() << "\n";
	roomDetails << " Player in Room: " << isPlayerInRoom() << "\n";
	roomDetails << " Hazards: " << getHazardsAsString() << "\n";
	roomDetails << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return roomDetails.str();
}



//-------------------------------------//
// mutator methods                     //
//-------------------------------------//

void Room::setNumber(int num) {
	if (roomNumber >= 0) {
		roomNumber = num;

	}
	else {
		displayString(" You have not entered a valid room number to set.\n");
	}
}


void Room::setName(string name){
	if (name.find_first_not_of(' ') != string::npos) {
		roomName = name;

	}
	else {
		displayString(" You have not entered a valid room name to set.\n");
	}
}


void Room::setDescription(string description) {
	if (description.find_first_not_of(' ') != string::npos) {
		roomDescription = description;

	}
	else {
		displayString(" You have not entered a valid room description to set.\n");
	}
}


void Room::setExitDirections(vector<string> directions) {
	if (!directions.empty()) {
		roomExitDirections = directions;
	}
	else {
		displayString(" You have not entered a valid room direction vector to set.\n");
	}
}


void Room::setExitConnections(vector<int> connections) {
	if (!connections.empty()) {
		roomExitConnections = connections;
	}
	else {
		displayString(" You have not entered a valid room connection vector to set.\n");
	}
}


void Room::setPlayerInRoom(bool isInRoom) {
	hasPlayer = isInRoom;
}


void Room::setHazards(vector<int> hazards){
	// sets a vector of hazard IDs as the room's fector of hazard ID's

	if (!hazards.empty()) {
		hazards = hazards;
	}
	else {
		displayString(" You have not entered a valid hazard vector to set.\n");
	}
}


void Room::addHazard(int hazard){
	// adds the input hazard ID to the hazards vector

	if (hazard >= 0) {
		hazards.push_back(hazard);

	}
	else {
		displayString(" You have not entered a valid hazard ID to add to the room.\n");
	}
}
 

void Room::removeHazard(int hazard){
	// removes the input hazard ID from the hazards vector

	if (hazard >= 0) {
		vector<int>::const_iterator iter;

		for (iter = hazards.begin(); iter != hazards.end(); iter++) {
			if (*iter == hazard) {
				hazards.erase(iter);
				break;
			}
		}
	}
	else {
		displayString(" You have not entered a valid hazard ID to remove from the room.\n");
	}
}
