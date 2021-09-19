/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Application Header File

The Header file for the main application that
controls the flow and logic of the game.

**************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

#include "CommonFuncs.h"
#include "GameEnums.h"
#include "Room.h"
#include "Item.h"
#include "Player.h"

using namespace std;


// file paths
const string TITLE_SCREEN_PATH = "ScreenData/TitleScreen.txt";
const string INFO_SCREEN_PATH = "ScreenData/InfoScreen.txt";
const string HOW_TO_SCREEN_PATH = "ScreenData/HowToScreen.txt";
const string MAP_DATA_PATH = "ScreenData/MapScreen.txt";

const string ROOM_DATA_PATH = "RoomData.txt";
const string ARIGAMO_DATA_PATH = "";
const string PITS_DATA_PATH = "";
const string CCRAT_DATA_PATH = "";
const string ORACLE_DATA_PATH = "";
const string THIEF_DATA_PATH = "";
const string RAIDERS_DATA_PATH = "";
const string TRADER_DATA_PATH = "";
const string KNIGHT_DATA_PATH = "";

// game constants
const int TOTAL_ROOMS = 20;

const int PLAYER_START_ROOM = 6;
const int ARIGAMO_START_ROOM = 19;

// game screens
string titleScreen;
string infoScreen;
string howToScreen;

// game variables
Difficulty difficulty = NORMAL;
//int totalStartingHazards;

Player player;
//vector<unique_ptr<Hazard>> hazards;
vector<Room*> ruinRooms;
//int roomConnections[TOTAL_ROOMS][TOTAL_ROOMS];

//vector<string> eventQueue;


// display functions
void displayTitle();
void displayInfo();
void displayHowTo();
void displayPlayerStats();
//void displayEventDescriptions();
void displayRoomInfo(int room);
void displayRoomExits(int room);
void displayMap();
//void displayEndScreen();
void displayUI();

// core game functons
void playGame();
void gameSetUp();
void gameLoop();
bool playerInputLoop();

PlayerAction getActionID(string action);
bool moveAction(const vector<string>& arguments);
bool shootAction(const vector<string>& arguments);
bool telecardAction(const vector<string>& arguments);
bool mapAction();
bool interactAction();
bool helpAction();

void initialiseRooms();
//void createRoomMatrix();
void removeRoomsVec(); 

//void initialiseHazards();
//void removeHazardsVec();

void setGameDifficulty();

//int getNumRoamingHazards();
//void updateHazards();
//void moveHazard();

// event management functions
//void updateEventQueue(vector<string> events);
//void clearEventQueue();

// player check functions
bool hasPlayerWon();
bool hasPlayerLost();

//int calculatePlayerScore();



#endif