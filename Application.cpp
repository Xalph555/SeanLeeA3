/**************************************************
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: Assignment 2 + 3
Author: Sean Lee

Purpose: Application Definition File

The Definition file for the main application that
controls the flow and logic of the game.

**************************************************/

#include "Application.h"


int main() {

	playGame();

	pause();
	return 0;
}



//-------------------------------------//
// display functions                   //
//-------------------------------------//

void displayTitle() {
	// displays the title of the game
	// usually signals the start of a new screen

	system("cls");
	cout << titleScreen;
}


void displayInfo() {
	// displays the game's starting info screen

	displayTitle();
	cout << infoScreen;
}


void displayHowTo() {
	// displays the game's "how to play" screen

	displayTitle();
	cout << howToScreen;
}


void displayPlayerStats() {
	// displays the player's stats screen

	cout << " Name: " << player.getName();
	cout << "\t\t\t\t\t\tHealth: " << player.getHealthCurrent() << "/" << player.getHealthMax() << "\n";
	cout << "\t\t\t\t\t\tIncense Sticks: " << player.getItem("Incense Sticks")->getAmount() << "\n";
	cout << "\t\t\t\t\t\tCrossbow Bolts: " << player.getItem("Crossbow Bolts")->getAmount() << "\n\n";

	cout << "Inventory: " << player.getInventoryAsString() << "\n";
	cout << "_______________________________________________________________________________\n";
}


//void displayEventDescriptions(){}


void displayRoomInfo(int room) {
	// displays the selected room's information

	cout << ruinRooms[room]->getRoomInfo() << "\n";
}


void displayRoomExits(int room) {
	// displays the selected room's exits and hints

	// display hints of nearby rooms - *placeholder
	cout << " This is a hazard hint from an adjacent room\n\n";
	cout << " This is a hazard hint from an adjacent room\n\n";
	
	// display room exits
	cout << ruinRooms[room]->getRoomExits();
	cout << "_______________________________________________________________________________\n";
}


void displayMap() {
	// displays the game's map

	displayTitle();
	cout<< player.getItem("Map")->getOtherData();
}


//void displayEndScreen(){}


void displayUI() {
	// displays the game's UI

	displayTitle();
	displayPlayerStats();
	displayRoomInfo(player.getCurrentRoom());

	//displayEventDescriptions();

	if (!player.isDisplaced()) {
		displayRoomExits(player.getCurrentRoom());
	}
}



//-------------------------------------//
// core game functions                 //
//-------------------------------------//

void playGame() {
	// handles the flow of the game from setup to end

	bool isPlaying = true;

	do {
		gameSetUp();
		gameLoop();

		isPlaying = getBoolInput(" Do you want to play again? (Y/N): ");

	} while (isPlaying);

	//displayEndScreen();

	// clean up heap
	//clearHazardsVec();
	removeRoomsVec();

	cout << "\n Thank you for playing!\n";
}


void gameSetUp() {
	// loads and sets up the core parts of the game

	// load and store required screens
	titleScreen = loadFileAsString(TITLE_SCREEN_PATH);
	infoScreen = loadFileAsString(INFO_SCREEN_PATH);
	howToScreen = loadFileAsString(HOW_TO_SCREEN_PATH);

	displayInfo();
	pause();

	displayHowTo();
	pause();

	// setting up game objects
	displayTitle();
	string playerName = getStringInput(" What is your name player?: ");

	initialiseRooms();

	player = Player(playerName, 30);
	player.setStartingRoom(ruinRooms, PLAYER_START_ROOM);

	// set game difficulty
	setGameDifficulty();

	//initialiseHazards();

	pause();
}


void gameLoop() {
	// handles the flow and progression of the main game

	bool hasQuit = false;

	while (!hasPlayerWon() && !hasPlayerLost() && !hasQuit) {
		
		//updateHazards();

		displayUI();

		if (!player.isDisplaced()) {
			// get player action
			hasQuit = playerInputLoop();

		}

		player.setDisplace(false);

		//clearEventQueue();
	}
}


bool playerInputLoop() {
	// handles the player's action during their turn

	bool isPlayerTurn = true;

	do {
		stringstream userInput("");

		string inputCommand = "";
		vector<string> inputArguments = {};

		cout << " (type HELP to bring up the help menu)\n";
		userInput << getStringInput(" What will you do?: ");

		// splitting components of input into command and arguments
		getline(userInput, inputCommand, ' ');

		while (userInput.good()) {
			string part = "";

			getline(userInput, part, ' ');
			inputArguments.push_back(part);
		}

		// run action
		switch (getActionID(inputCommand)) {
			case MOVE:
				isPlayerTurn = moveAction(inputArguments);

				if (isPlayerTurn) {
					cout << " Those are not valid arguments for the MOVE action.\n";
					pause();
					displayUI();
				}
				break;

			case SHOOT:
				isPlayerTurn = shootAction(inputArguments);

				if (isPlayerTurn) {
					cout << " Those are not valid arguments for the SHOOT action.\n";
					pause();
					displayUI();
				}
				break;

			case TELECARD:
				isPlayerTurn = telecardAction(inputArguments);

				if (isPlayerTurn) {
					cout << " Those are not valid arguments for the TELECARD action.\n";
					pause();
					displayUI();
				}
				break;

			case MAP:
				isPlayerTurn = mapAction();
				break;

			case INTERACT:
				isPlayerTurn = interactAction();
				break;

			case HELP:
				isPlayerTurn = helpAction();
				break;

			case QUIT:
				return true;

			default:
				cout << " That is not a valid ACTION. \n";
				pause();
				displayUI();
		}

	} while (isPlayerTurn);

	return false;
}


PlayerAction getActionID(string action) {
	// returns the action ID from the player's input action

	if (action == "MOVE") {
		return MOVE;

	}
	else if (action == "SHOOT") {
		return SHOOT;

	}
	else if (action == "TELECARD") {
		return TELECARD;

	}
	else if (action == "MAP") {
		return MAP;

	}
	else if (action == "INTERACT") {
		return INTERACT;

	}
	else if (action == "HELP") {
		return HELP;

	}
	else if (action == "QUIT") {
		return QUIT;

	}
	else {
		return NOACTION;
	}
}


bool moveAction(const vector<string>& arguments) {
	// handles validation and operation of player's MOVE action

	bool isPlayerTurn = true;

	if (arguments.size() == 1) {
		int targetRoom = ruinRooms[player.getCurrentRoom()]->getRoomConnection(arguments[0]);

		if (targetRoom != -1) {
			player.moveTo(ruinRooms, targetRoom);
			isPlayerTurn = false;
		}
	}

	return isPlayerTurn;
}


bool shootAction(const vector<string>& arguments) {
	// handles validation and operation of player's SHOOT action

	cout << " This is the SHOOT action. \n";
	pause();

	// validate input arguments first

	return false;
}


bool telecardAction(const vector<string>& arguments) {
	// handles validation and operation of player's TELECARD action

	cout << " This is the TELECARD action. \n";
	pause();

	// validate input arguments first

	return false;
}


bool mapAction() {
	// handles validation and operation of player's MAP action

	displayMap();
	pause();
	displayUI();

	return false;
}


bool interactAction() {
	// handles validation and operation of player's INTERACT action

	cout << " This is the INTERACT action. \n";
	pause();
	displayUI();

	return false;
}


bool helpAction() {
	// handles validation and operation of player's HELP action

	displayHowTo();
	pause();
	displayUI();

	return false;
}


void initialiseRooms() {
	// Initialises Abandon Ruin's rooms

	// load raw data into vector
	vector<string> roomData = loadFileAsVector(ROOM_DATA_PATH);

	unsigned int index = 0;

	while (index < roomData.size()) {
		int roomNum = 0;
		string roomName = "";
		stringstream roomDescription("");
		vector<string> roomExits = {};
		vector<int> roomConnections = {};

		// load room number
		roomNum = stoi(roomData[index]);
		index++;

		// load room name
		roomName = roomData[index];
		index++;

		// load room description
		index++;
		while (roomData[index] != "#") {
			roomDescription << " " + roomData[index] + "\n";
			index++;

		}
		index++;

		// load room exits
		stringstream exitsTemp(roomData[index]);

		while (exitsTemp.good()) {
			string exit = "";

			getline(exitsTemp, exit, ',');
			roomExits.push_back(exit);
		}
		index++;

		// load room connections
		exitsTemp.clear();
		exitsTemp.str(roomData[index]);

		while (exitsTemp.good()) {
			string connection = "";

			getline(exitsTemp, connection, ',');
			roomConnections.push_back(stoi(connection));
		}
		index++;

		// add new room object to vector on heap
		ruinRooms.push_back(new Room(roomNum, roomName, roomDescription.str(), roomExits, roomConnections));
	}

	//createRoomMatrix()
}


//void createRoomMatrix(){}


void removeRoomsVec(){
	// cleans up rooms from heap

	for (int i = ruinRooms.size()-1; i >= 0; --i) {
		delete ruinRooms[i];
		ruinRooms[i] = nullptr;
	}
}


//int getNumRoamingHazards(){int hazardsToInitialise[TOTAL_HAZARD_TYPES];}


//void initialiseHazards(){}


//void removeHazardsVec(){}


void setGameDifficulty() {
	// asks the user for the game's difficulty and applies the appropriate settings

	// present difficulty options to player
	displayTitle();
	cout << "\n Game Difficulty: [0] Amendment (EASY)\n";
	cout << " \t\t  [1] Atonement (NORMAL)\n";
	cout << " \t\t  [2] Redemption (HARD)\n\n";

	int userInput = getIntIntput(" Please select a difficulty according to their number: ", EASY, HARD);

	// generate player items
	vector<Item> items;
	items.push_back(Item("Enchanted Crossbow", WEAPON, 1));
	items.push_back(Item("Crossbow Bolts", CONSUMABLE, 0));
	items.push_back(Item("Protective Censer", MAGIC, 1));
	items.push_back(Item("Incense Sticks", CONSUMABLE, 0));
	items.push_back(Item("Telecard", CONSUMABLE, 1));
	items.push_back(Item("Map", NAVIGATION, 1));

	// load the game's map
	items[5].setOtherData(loadFileAsString(MAP_DATA_PATH));

	// apply appropriate settings
	switch (userInput) {
		case 0:
			difficulty = EASY;

			// *placeholder - apply easy difficulty settings

			cout << "\n Difficulty set to Amendment (EASY)\n";
			break;

		case 1:
			difficulty = NORMAL;

			// *placeholder - apply normal difficulty settings

			cout << "\n Difficulty set to Atonement (NORMAL)\n";
			break;

		case 2:
			difficulty = HARD;

			// *placeholder - apply hard difficulty settings

			cout << "\n Difficulty set to Redemption (HARD)\n";
			break;

		default:
			cout << "\n There was an error applying the right difficulty settings.\n";
	}

	player.setInventory(items);
}


//void updateHazards(){}
 

//void moveHazard(){}



//-------------------------------------//
// event management functions          //
//-------------------------------------//

//void updateEventQueue(vector<string> events){}


//void clearEventQueue(){}



//-------------------------------------//
// player check functions              //
//-------------------------------------//

bool hasPlayerWon(){
	// checks whether the player has won

	// *placeholder
	return false;
}


bool hasPlayerLost(){
	// checks whether the player has lost

	//  *placeholder
	return false;

}


//int calculatePlayerScore(){}