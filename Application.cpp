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
	srand(unsigned(time(NULL)));

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
	displayString(titleScreen);
}


void displayInfo() {
	// displays the game's starting info screen

	displayTitle();
	displayString(infoScreen);
}


void displayHowTo() {
	// displays the game's "how to play" screen

	displayTitle();
	displayString(howToScreen);
}


void displayPlayerStats() {
	// displays the player's stats screen

	displayString(" Name: " + player.getName());
	displayString("\t\t\t\t\t\tHealth: " + to_string(player.getHealthCurrent()) + "/" + to_string(player.getHealthMax()) + "\n");
	displayString("\t\t\t\t\t\tIncense Sticks: " + to_string(player.getItem("Incense Sticks")->getAmount()) + "\n");
	displayString("\t\t\t\t\t\tCrossbow Bolts: " + to_string(player.getItem("Crossbow Bolts")->getAmount()) + "\n\n");

	displayString("Inventory: " + player.getInventoryAsString() + "\n");
	displayString("_______________________________________________________________________________\n");
}


void displayEventDescriptions(){
	// displays the strings contained within eventQueue.

	vector<string> eventQueueTemp = eventQueue.getEventQueueContents();
	vector<string>::const_iterator iter;

	for (iter = eventQueueTemp.begin(); iter != eventQueueTemp.end(); iter++) {
		string eventDetails = *iter;

		if (eventDetails != "$") {
			displayString(eventDetails + "\n");

		}
		else {
			break;
		}
	}

	//displayString() << "\n";
}


void displayRoomInfo(int room) {
	// displays the selected room's information

	displayString(ruinRooms.getRoom(room)->getRoomInfo() + "\n");
}


void displayRoomExits(int room) {
	// displays the selected room's exits and hints

	// display hints of nearby rooms
	vector<int> connectedRooms = ruinRooms.getRoom(room)->getExitConnections();

	for (unsigned int i = 0; i < connectedRooms.size(); i++) {
		if (ruinRooms.getRoom(connectedRooms[i])->hasHazard()) {
			vector<int> roomHazards = ruinRooms.getRoom(connectedRooms[i])->getHazards();

			for (unsigned int j = 0; j < roomHazards.size(); j++) {
				Hazard* hazTemp = hazards.getHazard(roomHazards[j]);

				if (hazTemp->isRoaming()) {
					if (!hazTemp->hasDied() && hazTemp->conscious()) {
						displayString(hazTemp->getHint() + "\n\n");
					}
				}
				else {
					displayString(hazTemp->getHint() + "\n\n");
				}
			}
		}
	}

	// display room exits
	displayString(ruinRooms.getRoom(room)->getRoomExits());
}


void displayMap() {
	// displays the game's map

	displayTitle();
	displayString(player.getItem("Map")->getOtherData());
}


void displayEndScreen(){
	// displays the ending screen of the game

	displayTitle();

	if (hasPlayerWon()) {
		displayString("\t\t\t\tYou WIN!\n\n");

	}
	else {
		displayString("\t\t\t\tYou LOSE!\n\n");
	}

	displayString("\t\tName: " + player.getName() + "\n\n");
	displayString("\t\tHealth: " + to_string(player.getHealthCurrent()) + "/" + to_string(player.getHealthMax()) + "\n");
	displayString("\t\tRemaining Incense Sticks: " + to_string(player.getItemAmount("Incense Sticks")) + "\n");
	displayString("\t\tRemaining Crossbow Bolts: " + to_string(player.getItemAmount("Crossbow Bolts")) + "\n");

	string hasTelecard = (player.getItemAmount("Telecard") > 0) ? "Yes" : "No";
	displayString("\t\tHas used Telecard: " + hasTelecard + "\n");

	displayString("\t\tNumber of Roaming Opponents Alive: " + to_string(hazards.getNumRoamingHazards()) + "\n");

	string isArigamoDead = (hazards.getHazard("Arigamo")->hasDied()) ? "Yes" : "No";
	displayString("\t\tHas Arigamo been slain: " + isArigamoDead + "\n");

	string hasGem = (player.hasItem("Fuhai Gem")) ? "Yes" : "No";
	displayString("\t\tHas Fuhai Gem been retrieved: " + hasGem + "\n");

	displayString("\t\tScore Multiplier: " + to_string(difficulty + 1) + "\n");

	displayString("\n\t\tFINAL SCORE: " + to_string(calculatePlayerScore()) + "\n");

	displayString("_______________________________________________________________________________\n");
}


void displayUI() {
	// displays the game's UI

	displayTitle();
	displayPlayerStats();
	displayRoomInfo(player.getCurrentRoom());

	displayEventDescriptions();

	if (!player.isDisplaced() && !hasPlayerLost() && !hasPlayerWon()) {
		displayRoomExits(player.getCurrentRoom());
	}

	displayString("_______________________________________________________________________________\n");
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

		displayEndScreen();

		isPlaying = getBoolInput(" Do you want to play again? (Y/N): ");

	} while (isPlaying);

	displayString("\n Thank you for playing!\n");
}


void gameSetUp() {
	// loads and sets up the core parts of the game

	// load and store required screens
	titleScreen = loadFileAsString(TITLE_SCREEN_PATH);
	infoScreen = loadFileAsString(INFO_SCREEN_PATH);
	howToScreen = loadFileAsString(HOW_TO_SCREEN_PATH);

	eventQueue = EventQueue();

	displayInfo();
	pause();

	displayHowTo();
	pause();

	// setting up game objects
	displayTitle();

	hazards = HazardContainer();
	string playerName = getStringInput(" What is your name player?: ");

	initialiseRooms();

	player = Player(playerName, 30);
	player.setStartingRoom(ruinRooms, PLAYER_START_ROOM);

	// set game difficulty
	setGameDifficulty();

	initialiseHazards();

	pause();
}


void gameLoop() {
	// handles the flow and progression of the main game

	totalTurns = 0;
	bool hasQuit = false;

	do {
		totalTurns++;

		updateHazards();
		displayUI();

		if (!hasPlayerWon() && !hasPlayerLost() && !hasQuit) {
			if (!player.isDisplaced()) {
				hasQuit = playerInputLoop();

			}
			else {
				player.updateDisplacement();
				pause();
			}
		}

		eventQueue.clearEventQueue();

	} while (!hasPlayerWon() && !hasPlayerLost() && !hasQuit);

	if (!hasQuit) {
		if (hasPlayerWon()) {
			displayString("\n You have Redeemed yourself!\n");
			pause();

		}
		else if (hasPlayerLost()) {
			displayString("\n You have Lost!\n");
			pause();
		}
	} 
}


bool playerInputLoop() {
	// handles the player's action during their turn

	bool isPlayerTurn = true;

	do {
		stringstream userInput("");

		string inputCommand = "";
		vector<string> inputArguments = {};

		displayString(" (type HELP to bring up the help menu)\n");
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
				if (player.getItemAmount("Incense Sticks") > 0) {
					isPlayerTurn = moveAction(inputArguments);

					if (isPlayerTurn) {
						displayString(" Those are not valid arguments for the MOVE action.\n");
						pause();
						displayUI();
					}
				}
				else {
					displayString(" You do not have any 'Incense Sticks' left.\n");
					pause();
					displayUI();
				}

				break;

			case SHOOT:
				if (player.getItemAmount("Crossbow Bolts") > 0) {
					isPlayerTurn = shootAction(inputArguments);

					if (isPlayerTurn) {
						displayString(" Those are not valid arguments for the SHOOT action.\n");
						pause();
						displayUI();
					}
				}
				else {
					displayString(" You do not have any 'Crossbow Bolts' left.\n");
					pause();
					displayUI();
				}
				
				break;

			case TELECARD:
				if (player.getItemAmount("Telecard") > 0) {
					isPlayerTurn = telecardAction(inputArguments);

					if (isPlayerTurn) {
						displayString(" Those are not valid arguments for the TELECARD action or you have not visited that Room yet.\n");
						pause();
						displayUI();
					}
				}
				else {
					displayString(" You do not have any 'Telecards' left.\n");
					pause();
					displayUI();
				}

				break;

			case MAP:
				if (player.hasItem("Map")) {
					isPlayerTurn = isPlayerTurn = mapAction();

				}
				else {
					displayString(" You do not have a Map.\n");
					pause();
					displayUI();
				}

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
				displayString(" That is not a valid ACTION. \n");
				pause();
				displayUI();
		}

	} while (isPlayerTurn);

	return false;
}


void setGameDifficulty() {
	// asks the user for the game's difficulty and applies the appropriate settings

	// present difficulty options to player
	displayTitle();
	displayString("\n Game Difficulty: [0] Amendment (EASY)\n");
	displayString(" \t\t  [1] Atonement (NORMAL)\n");
	displayString(" \t\t  [2] Redemption (HARD)\n\n");

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

	// hazards which must always be present
	hazardsToInitialise[ARIGAMO] = 1;
	hazardsToInitialise[PIT] = 2;
	hazardsToInitialise[CCRAT] = 2;
	hazardsToInitialise[ORACLE] = 1;
	hazardsToInitialise[THIEF] = 1;
	hazardsToInitialise[RAIDERS] = 1;
	hazardsToInitialise[TRADER] = 1;
	hazardsToInitialise[KNIGHT] = 1;

	// apply appropriate settings
	switch (userInput) {
		case 0:
			difficulty = EASY;

			items[1].setAmount(8);
			items[3].setAmount(20);

			displayString("\n Difficulty set to Amendment (EASY)\n");
			break;

		case 1:
			difficulty = NORMAL;

			items[1].setAmount(5);
			items[3].setAmount(15);

			displayString("\n Difficulty set to Atonement (NORMAL)\n");
			break;

		case 2:
			difficulty = HARD;

			items[1].setAmount(3);
			items[3].setAmount(12);


			displayString("\n Difficulty set to Redemption (HARD)\n");
			break;

		default:
			displayString("\n There was an error applying the correct difficulty settings.\n");
	}

	player.setInventory(items);
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
		int targetRoom = ruinRooms.getRoom(player.getCurrentRoom())->getRoomConnection(arguments[0]);

		if (targetRoom != -1) {
			player.moveTo(ruinRooms, targetRoom, false);
			isPlayerTurn = false;
		}
	}

	return isPlayerTurn;
}


bool shootAction(const vector<string>& arguments) {
	// handles validation and operation of player's SHOOT action

	bool isPlayerTurn = true;

	vector<string> boltHints;

	boltHints = player.shootBolt(ruinRooms, hazards, arguments);

	// display hints bolt has found
	if (!boltHints.empty()) {
		vector<string>::const_iterator hint;

		displayString("\n");

		for (hint = boltHints.begin(); hint != boltHints.end(); hint++) {
			string hintTemp = *hint;
			displayString(hintTemp + "\n");
		}

		pause();
		isPlayerTurn = false;
	}

	return isPlayerTurn;
}


bool telecardAction(const vector<string>& arguments) {
	// handles validation and operation of player's TELECARD action

	bool isPlayerTurn = true;

	if (arguments.size() == 1 && isNumber(arguments[0])) {
		if (player.hasVisitedRoom(stoi(arguments[0]))) {
			player.moveTo(ruinRooms, stoi(arguments[0]), false);
			player.getItem("Telecard")->updateAmount(-1);

			displayString("\n You Teleported!\n");
			pause();

			isPlayerTurn = false;
		}
	}

	return isPlayerTurn;
}


bool mapAction() {
	// handles validation and operation of player's MAP action

	displayMap();
	pause();
	displayUI();

	return true;
}


bool interactAction() {
	// handles validation and operation of player's INTERACT action

	vector<int> hazardsInRoom = ruinRooms.getRoom(player.getCurrentRoom())->getHazards();

	if (!hazardsInRoom.empty()){
		vector<int>::const_iterator iter;

		for (iter = hazardsInRoom.begin(); iter != hazardsInRoom.end(); iter++) {
			int hazID = *iter;
			Hazard* hazTemp = hazards.getHazard(hazID);

			switch (hazTemp->getType()) {
				case ORACLE:
					dynamic_cast<Oracle*>(hazTemp)->roomInteraction(player, hazards.getHazard("Arigamo")->getCurrentRoom());
					break;

				default:
					hazTemp->roomInteraction();
			}
		}
	}
	else {
		displayString("\n There is nothing in the Room to interact with.");
	}
	
	pause();
	displayUI();

	return true;
}


bool helpAction() {
	// handles validation and operation of player's HELP action

	displayHowTo();
	pause();
	displayUI();

	return true;
}



void initialiseRooms() {
	// Initialises Abandon Ruin's rooms

	ruinRooms = RoomContainer();

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
		Room* newRoom = new Room(roomNum, roomName, roomDescription.str(), roomExits, roomConnections);
		ruinRooms.addRoom(newRoom);
	}

	createRoomMatrix();
}


void createRoomMatrix(){
	vector<Room*>::const_iterator iter;

	for (int i = 0; i < TOTAL_ROOMS; i++) {
		int currentRoom = ruinRooms.getRoom(i)->getNumber();
		vector<int> connections = ruinRooms.getRoom(i)->getExitConnections();

		vector<int>::const_iterator cons;

		for (cons = connections.begin(); cons != connections.end(); cons++) {
			int con = *cons;

			roomConnections[currentRoom][con] = 1;
			roomConnections[con][currentRoom] = 1;

		}
	}
}


void initialiseHazards() {
	// Initialises the game's hazards

	for (int i = 0; i < TOTAL_HAZARD_TYPES - 1; i++) {
		if (hazardsToInitialise[i] > 0) {
			loadHazard((HazardType) i, hazardsToInitialise[i]);

		}
	}
}


void loadHazard(HazardType type, int amount) {
	// loads and initialises a specific hazard into the game

	if (amount != 0) {
		// load raw data into vector
		vector<string> hazardData = loadFileAsVector(HAZARD_DATA_PATHS[type]);

		string hazardName = "";
		string hazardHint = "";
		vector<string> eventDescriptions = {};
		bool isRoaming = false;
		bool isConscious = false;

		int index = 0;

		// load hazard name
		hazardName = hazardData[index];
		index++;

		// load hazard hint
		hazardHint = " " + hazardData[index];
		index++;

		// load hazard event description
		index++;
		while (hazardData[index] != "$") {
			stringstream hazardEvent("");

			while (hazardData[index] != "#") {
				hazardEvent << " " << hazardData[index] + "\n";
				index++;
			}

			eventDescriptions.push_back(hazardEvent.str());
			index++;
		}
		index++;

		// load isRoaming
		isRoaming = stoi(hazardData[index]);
		index++;

		// load isLiving
		isConscious = stoi(hazardData[index]);
		index++;


		// initiaise correct amount of hazard
		vector<int> exceptionRooms = {PLAYER_START_ROOM, ARIGAMO_START_ROOM};

		switch (type) {
			case ARIGAMO: {
				// create required extra variables
				int hpDrain = 2 * (difficulty + 1);
				float baseRoam = abs(((difficulty + 1) * 0.25) - 0.4);

				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Arigamo(hazardName, ARIGAMO, hazardHint, eventDescriptions, isRoaming, isConscious, hpDrain, baseRoam);

					hazards.addHazard(newHazard);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, ARIGAMO_START_ROOM);
				}
				break;
			}

			case PIT: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Pit(hazardName, PIT, hazardHint, eventDescriptions, isRoaming, isConscious);

					hazards.addHazard(newHazard);

					int startRoom = ruinRooms.findRandomEmptyStartRoom(exceptionRooms);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break; 
			}

			case CCRAT: {
				// create required extra variables
				int damage = (difficulty + 1) * 2;

				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new CCRats(hazardName, CCRAT, hazardHint, eventDescriptions, isRoaming, isConscious, damage);

					hazards.addHazard(newHazard);

					int startRoom = ruinRooms.findRandomEmptyStartRoom(exceptionRooms);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break;
			}
			
			case ORACLE: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Oracle(hazardName, ORACLE, hazardHint, eventDescriptions, isRoaming, isConscious);

					hazards.addHazard(newHazard);

					int startRoom = ruinRooms.findRandomEmptyStartRoom(exceptionRooms);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break; 
			}
				
			case THIEF: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Thief(hazardName, THIEF, hazardHint, eventDescriptions, isRoaming, isConscious);

					hazards.addHazard(newHazard);

					int startRoom = ruinRooms.findRandomEmptyStartRoom(exceptionRooms);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break; 
			}
				
			case RAIDERS: {
				// create required extra variables
				int damage = (difficulty + 1) * 3;

				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Raiders(hazardName, RAIDERS, hazardHint, eventDescriptions, isRoaming, isConscious, damage);

					hazards.addHazard(newHazard);

					int startRoom = ruinRooms.findRandomEmptyStartRoom(exceptionRooms);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break; 
			}
				
			case TRADER: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Trader(hazardName, TRADER, hazardHint, eventDescriptions, isRoaming, isConscious);

					hazards.addHazard(newHazard);

					int startRoom = ruinRooms.findRandomEmptyStartRoom(exceptionRooms);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break; 
			}
				
			case KNIGHT: {
				// create required extra variables
				int damage = (difficulty + 1) * 4;

				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Knight(hazardName, KNIGHT, hazardHint, eventDescriptions, isRoaming, isConscious, damage);

					hazards.addHazard(newHazard);

					int startRoom = ruinRooms.findRandomEmptyStartRoom(exceptionRooms);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break;
			}

			default:
				displayString(" The hazard could not be initialised \n");
		}
	}
}


void updateHazards(){
	// updates the game's hazards 

	if (!player.isDisplaced() && totalTurns > 1) {
		moveHazards();
	}

	// updating interactions
	vector<string> eventTemp;

	Arigamo* arigamo = dynamic_cast<Arigamo*>(hazards.getHazard("Arigamo"));

	eventTemp = arigamo->drainPlayerHP((int*)roomConnections, TOTAL_ROOMS, player);
	eventQueue.updateEventQueue(eventTemp);
	
	// check arigamo interactions with player
	if (arigamo->getCurrentRoom() == player.getCurrentRoom()) {
		eventTemp = arigamo->updateInteraction(player);
		eventQueue.updateEventQueue(eventTemp);
	}

	// check arigamo interactions with other hazards in the same room
	if (ruinRooms.getRoom(arigamo->getCurrentRoom())->hasHazard()) {
		vector<int> hazardsInRoom = ruinRooms.getRoom(arigamo->getCurrentRoom())->getHazards();
		vector<int>::const_iterator iter;

		for (iter = hazardsInRoom.begin(); iter != hazardsInRoom.end(); iter++) {
			int hazID = *iter;

			if (hazID != arigamo->getID()) {
				eventTemp = arigamo->updateInteraction(hazards.getHazard(hazID));
				eventQueue.updateEventQueue(eventTemp);
			}
		}
	}

	// check other hazard's interaction with the player
	vector<int> hazardsInRoom = ruinRooms.getRoom(player.getCurrentRoom())->getHazards();
	vector<int>::const_iterator iter;

	for (iter = hazardsInRoom.begin(); iter != hazardsInRoom.end(); iter++) {
		int hazID = *iter;
		Hazard* hazTemp = hazards.getHazard(hazID);

		switch (hazTemp->getType()) {
			case PIT: 
				eventTemp = dynamic_cast<Pit*>(hazTemp)->updateInteraction(player);
				eventQueue.updateEventQueue(eventTemp);
				break;
			
			case CCRAT: 
				eventTemp = dynamic_cast<CCRats*>(hazTemp)->updateInteraction(player, ruinRooms);
				eventQueue.updateEventQueue(eventTemp);
				break;
			
			case ORACLE: 
				eventTemp = dynamic_cast<Oracle*>(hazTemp)->updateInteraction(player);
				eventQueue.updateEventQueue(eventTemp);
				break;
			
			case THIEF: 
				eventTemp = dynamic_cast<Thief*>(hazTemp)->updateInteraction(player);
				eventQueue.updateEventQueue(eventTemp);
				break;
			
			case RAIDERS: 
				eventTemp = dynamic_cast<Raiders*>(hazTemp)->updateInteraction(player, ruinRooms);
				eventQueue.updateEventQueue(eventTemp);
				break;
			
			case TRADER: 
				eventTemp = dynamic_cast<Trader*>(hazTemp)->updateInteraction(player);
				eventQueue.updateEventQueue(eventTemp);
				break;
			
			case KNIGHT: 
				eventTemp = dynamic_cast<Knight*>(hazTemp)->updateInteraction(player);
				eventQueue.updateEventQueue(eventTemp);
				break;
			
			default:
				displayString(" There is no Hazard interaction with the player.\n");
		}
	}
}
 

void moveHazards(){
	// moves the hazards in the game if they are able to

	// move Arigamo
	Arigamo* arigamo = dynamic_cast<Arigamo*>(hazards.getHazard("Arigamo"));

	if (!arigamo->hasDied()) {
		arigamo->updateTurnsToWake(-1);
		arigamo->wakeArigamo(hazards.getNumRoamingHazards());

		if (!arigamo->isSleeping()) {
			vector<int> connectedRooms = ruinRooms.getRoom(arigamo->getCurrentRoom())->getExitConnections();
			int nextRoom = connectedRooms[rand() % connectedRooms.size()];

			arigamo->moveTo(ruinRooms, nextRoom);

			arigamo->resetTurnsToWake();
			arigamo->setIsAsleep(true);
			eventQueue.updateEventQueue(arigamo->getEventDescriptions()[4]);

		}
	}
		
	// move other hazards
	vector<Hazard*>::const_iterator iter;
	vector<Hazard*> hazardsTemp = *hazards.getHazardsVector();

	vector<int> exceptionRooms = { arigamo->getCurrentRoom() };

	for (iter = hazardsTemp.begin(); iter != hazardsTemp.end(); iter++) {
		if ((*iter)->getType() != ARIGAMO && (*iter)->isRoaming() && !(*iter)->hasDied() && (*iter)->conscious()) {
			bool willMove = rand() % 2;

			if (willMove) {
				int nextRoom = ruinRooms.findEmptyAdjRoom((*iter)->getCurrentRoom(), exceptionRooms);

				if (nextRoom != -1) {
					(*iter)->moveTo(ruinRooms, nextRoom);
				}
			}
		}
	}
}


//-------------------------------------//
// player check functions              //
//-------------------------------------//

bool hasPlayerWon(){
	// checks whether the player has won

	// arigamo has been slained and player has retrieved gem
	if (hazards.getHazard("Arigamo")->hasDied() && player.hasItem("Fuhai Gem")) {
		return true;

	}
	else {
		return false;
	}
}


bool hasPlayerLost(){
	// checks whether the player has lost

	// player has run out of HP
	if (player.getHealthCurrent() == 0) {
		return true;
	}

	// player has run out of bolts
	else if (player.getItemAmount("Crossbow Bolts") == 0) {
		return true;
	}

	// player has run out of sticks
	else if (player.getItemAmount("Incense Sticks") == 0) {
		return true;
	}

	// player is in arigamo room and has not retrieved gem
	else if (hazards.getHazard("Arigamo")->hasDied() && hazards.getHazard("Arigamo")->interacted() && !player.hasItem("Fuhai Gem")) {
		return true;
	}

	// player has not lost
	else {
		return false;
	}
}


int calculatePlayerScore(){
	// calculates the player's final score

	int score = 0;

	score += player.getHealthCurrent() * 20;
	score += player.getItemAmount("Incense Sticks") * 5;
	score += player.getItemAmount("Crossbow Bolts") * 10;
	score += player.getItemAmount("Telecard") * 10;
	score += hazards.getHazard("Arigamo")->hasDied() * 200;
	score += player.hasItem("Fuhai Gem") * 200;
	score *= (difficulty + 1);

	return score;
}