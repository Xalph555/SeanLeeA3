/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Common Functons Definition File

The Definition file for Common Functions that
provide generic functionality to the game.

**************************************************/

#include "CommonFuncs.h"


void pause() {
	// pauses the program until the player presses a key

	displayString("\n\n\t");
	cin.clear();
	system("pause");
}


void displayString(string input) {
	// displays the string input

	cout << input;
}


string getStringInput(string question) {
	// retrieves a string input from the player

	string userInput = "";

	while (userInput.find_first_not_of(' ') == string::npos) {
		displayString("\n" + question);
		cin.clear();

		getline(cin, userInput);

		if (userInput.find_first_not_of(' ') == string::npos) {
			displayString("\n That is an invalid input.");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}
	}

	return stringUpperCase(userInput);
}


int getIntIntput(string question, int min, int max) {
	// retrieves an int input from the player

	int userInput = -1;

	do {
		displayString("\n" + question);
		cin.clear();

		cin >> userInput;

		if (userInput < min || userInput > max || cin.fail()) {
			displayString("\n That is an invalid input.");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			userInput = min - 1;

		}
	} while (userInput < min || userInput > max);

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return userInput;
}


char getCharInput(string question, char options[]) {
	// retrieves a char input from the player

	char userInput = '.';
	bool isFound = false;

	do {
		displayString("\n" + question);
		cin.clear();

		cin >> userInput;

		for (int i = 0; i < sizeof(options); i++) {
			if (toupper(userInput) == options[i]) {
				isFound = true;
			}
		}

		if (!isFound || cin.fail()) {
			displayString("\n That is an invalid input.");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}

	} while (!isFound || cin.fail());

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return toupper(userInput);
}


bool getBoolInput(string question) {
	// retrieves a bool input from the player

	char choices[] = { 'Y', 'N' };
	char userChoice = getCharInput(question, choices);

	if (userChoice == 'Y') {
		return true;

	}
	else {
		return false;
	}
}


bool isNumber(const string& input) {
	// checks whether the input string contains only digits

	bool result = true;

	if (input.find_first_not_of(' ') != string::npos) {
		string::const_iterator stringChar;
		for (stringChar = input.begin(); stringChar != input.end(); stringChar++) {
			if (!isdigit(*stringChar)) {
				result = false;

			}
		}
	}
	else {
		result = false;
	}

	return result;
}


bool areArgsValid(const vector<string>& arguments, const vector<string> validArgs) {
	// checks whether the strings in the arguments vector are valid by comparing them to the possible valid arguments contained in the validArgs input vector

	vector<string>::const_iterator iter;

	for (iter = arguments.begin(); iter != arguments.end(); iter++) {
		if (find(validArgs.begin(), validArgs.end(), *iter) == validArgs.end()) {
			return false;
		}
	}

	return true;
}


string stringUpperCase(string inputString) {
	// converts the characters of input string into upper case
	// adapted from Week 4 Lecture Slides

	transform(inputString.begin(), inputString.end(), inputString.begin(), toupper);
	return inputString;
}


string loadFileAsString(string fileName) {
	// reads data from a text file and returns it as a string
	// adapted from Week 6 Lecture Slides

	stringstream fileOutput;

	ifstream fileToRead(fileName);

	if (fileToRead.is_open()) {
		string line = "";

		while (!fileToRead.eof()) {
			getline(fileToRead, line);

			fileOutput << line << "\n";
		}
	}
	else {
		displayString("\n The file " + fileName + " was not found.");
	}

	fileToRead.close();

	return fileOutput.str();
}


vector<string> loadFileAsVector(string fileName) {
	// reads data from a text file and returns it as a vector of strings

	vector<string> fileOutput;

	ifstream fileToRead(fileName);

	if (fileToRead.is_open()) {
		string line = "";

		while (!fileToRead.eof()) {
			getline(fileToRead, line);

			if (line.find_first_not_of(' ') != string::npos) {
				fileOutput.push_back(line);
			}
		}
	}
	else {
		displayString("\n The file " + fileName + " was not found.");
	}

	fileToRead.close();

	return fileOutput;
}