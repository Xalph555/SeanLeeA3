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

using namespace std;


void pause();
void displayString();
string getStringInput(string question);
int getIntIntput(string question, int min, int max);
char getCharInput(string question, char options[]);
bool getBoolInput(string question);

bool isNumber(const string& input);

string loadFileAsString(string fileName);
vector<string> loadFileAsVector(string fileName);



#endif
