/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Enum Header File

The Header file that contains the enums for the 
game.

**************************************************/

#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H


// game difficulty
enum Difficulty {
	EASY,
	NORMAL,
	HARD

};


// the actions avaliable to the player
enum PlayerAction {
	NOACTION,
	MOVE,
	SHOOT,
	TELECARD,
	MAP,
	INTERACT,
	HELP,
	QUIT
};


// the types of items in the game
enum ItemType{
	NOITEM,
	WEAPON,
	CONSUMABLE,
	NAVIGATION,
	MAGIC
};


// the types of hazards in the game
const int TOTAL_HAZARD_TYPES = 9;
enum HazardType {
	ARIGAMO,
	PIT,
	CCRAT,
	ORACLE,
	THIEF,
	RAIDERS,
	TRADER,
	KNIGHT,
	NOHAZARD
};



#endif