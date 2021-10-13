/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Common Functons Header File

The Header file for Common Functions that 
provide generic functionality to the game.

**************************************************/

#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <ctime>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;

// other functions
void pause();
void displayString(string input);
string stringUpperCase(string inputString);

// input functions
string getStringInput(string question);
int getIntIntput(string question, int min, int max);
char getCharInput(string question, char options[]);
bool getBoolInput(string question);

// validation functions
bool isNumber(const string& input);
bool areArgsValid(const vector<string>& arguments, const vector<string> validArgs);

// file functions
string loadFileAsString(string fileName);
vector<string> loadFileAsVector(string fileName);



#endif
