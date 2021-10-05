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

	/*
	initialiseRooms();

	player = Player("Apples", 30);
	player.setStartingRoom(ruinRooms, 12);

	vector<string> test = {"test", "test2", "test3"};
	Arigamo ari = Arigamo(999, "Arigamo", ARIGAMO, "Death", test, true, true, 20, 0.5);
	ari.setStartingRoom(ruinRooms, ARIGAMO_START_ROOM);

	vector<string> testass = ari.drainPlayerHP((int*) roomConnections, TOTAL_ROOMS, player);
	
	*/

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


void displayEventDescriptions(){
	// displays the strings contained within eventQueue.

	vector<string>::const_iterator iter;

	for (iter = eventQueue.begin(); iter != eventQueue.end(); iter++) {
		string eventDetails = *iter;

		cout << eventDetails << "\n";
	}

	//cout << "\n";
}


void displayRoomInfo(int room) {
	// displays the selected room's information

	cout << ruinRooms[room]->getRoomInfo() << "\n";
}


void displayRoomExits(int room) {
	// displays the selected room's exits and hints

	// display hints of nearby rooms
	vector<int> connectedRooms = ruinRooms[room]->getExitConnections();

	for (int i = 0; i < connectedRooms.size(); i++) {
		if (ruinRooms[connectedRooms[i]]->hasHazard()) {
			vector<int> roomHazards = ruinRooms[connectedRooms[i]]->getHazards();

			for (int j = 0; j < roomHazards.size(); j++) {
				cout << hazards.getHazard(roomHazards[j])->getHint() << "\n\n";
			}
		}
	}

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

	displayEventDescriptions();

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

	while (!hasPlayerWon() && !hasPlayerLost() && !hasQuit) {
		totalTurns++;

		updateHazards();

		displayUI();

		if (!hasPlayerWon() && !hasPlayerLost() && !hasQuit) {
			if (!player.isDisplaced()) {
				// get player action
				hasQuit = playerInputLoop();

			}
			else {
				player.updateDisplacement();
				pause();
			}
			
		}

		clearEventQueue();
	}

	//pause();
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
				if (player.getItem("Crossbow Bolts")->getAmount() > 0) {
					isPlayerTurn = shootAction(inputArguments);

					if (isPlayerTurn) {
						cout << " Those are not valid arguments for the SHOOT action.\n";
						pause();
						displayUI();
					}
				}
				else {
					cout << " You do not have any 'Crossbow Bolts' left.\n";
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

	// hazards which must always be present
	hazardsToInitialise[ARIGAMO] = 1;
	hazardsToInitialise[PIT] = 3;
	hazardsToInitialise[CCRAT] = 2;

	// apply appropriate settings
	switch (userInput) {
		case 0:
			difficulty = EASY;

			items[1].setAmount(8);
			items[3].setAmount(20);

			cout << "\n Difficulty set to Amendment (EASY)\n";
			break;

		case 1:
			difficulty = NORMAL;

			items[1].setAmount(5);
			items[3].setAmount(15);

			cout << "\n Difficulty set to Atonement (NORMAL)\n";
			break;

		case 2:
			difficulty = HARD;

			items[1].setAmount(3);
			items[3].setAmount(12);


			cout << "\n Difficulty set to Redemption (HARD)\n";
			break;

		default:
			cout << "\n There was an error applying the right difficulty settings.\n";
	}

	for (int i = 0; i < difficulty + 1; i++) {
		int choice = rand() % 5 + 3;
		//hazardsToInitialise[choice] += 1;

		hazardsToInitialise[TRADER] += 1;

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
		int targetRoom = ruinRooms[player.getCurrentRoom()]->getRoomConnection(arguments[0]);

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

		cout << "\n";

		for (hint = boltHints.begin(); hint != boltHints.end(); hint++) {
			string hintTemp = *hint;
			cout << hintTemp << "\n";
		}

		pause();
		isPlayerTurn = false;
	}

	return isPlayerTurn;
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

	vector<int> hazardsInRoom = ruinRooms[player.getCurrentRoom()]->getHazards();

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
		cout << "\n There is nothing in the Room to interact with.";
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

	createRoomMatrix();
}


void createRoomMatrix(){
	vector<Room*>::const_iterator iter;

	for (iter = ruinRooms.begin(); iter != ruinRooms.end(); iter++) {
		Room* room = *iter;

		int currentRoom = room->getNumber();
		vector<int> connections = room->getExitConnections();

		vector<int>::const_iterator cons;

		for (cons = connections.begin(); cons != connections.end(); cons++) {
			int con = *cons;

			roomConnections[currentRoom][con] = 1;
			roomConnections[con][currentRoom] = 1;
		}
	}
}


void removeRoomsVec(){
	// cleans up rooms from heap

	for (int i = ruinRooms.size()-1; i >= 0; --i) {
		delete ruinRooms[i];
		ruinRooms[i] = nullptr;
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
		bool isLiving = false;

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
		isLiving = stoi(hazardData[index]);
		index++;


		// initiaise correct amount of hazard
		switch (type) {
			case ARIGAMO: {
				// create required extra variables
				int hpDrain = 2 * (difficulty + 1);
				float baseRoam = abs(((difficulty + 1) * 0.25) - 0.4);

				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Arigamo(hazardName, ARIGAMO, hazardHint, eventDescriptions, isRoaming, isLiving, hpDrain, baseRoam);

					hazards.addHazard(newHazard);
					hazards.getLastHazard()->setStartingRoom(ruinRooms, ARIGAMO_START_ROOM);
				}

				break;
			}

			case PIT: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Pit(hazardName, PIT, hazardHint, eventDescriptions, isRoaming, isLiving);

					hazards.addHazard(newHazard);

					int startRoom = findRandomEmptyRoom();
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}

				break; 
			}

			case CCRAT: {
				// create required extra variables
				int damage = (difficulty + 1) * 2;

				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new CCRats(hazardName, CCRAT, hazardHint, eventDescriptions, isRoaming, isLiving, damage);

					hazards.addHazard(newHazard);

					int startRoom = findRandomEmptyRoom();
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}

				break;
			}
			
			case ORACLE: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Oracle(hazardName, ORACLE, hazardHint, eventDescriptions, isRoaming, isLiving);

					hazards.addHazard(newHazard);

					int startRoom = findRandomEmptyRoom();
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}

				break; 
			}
				
			case THIEF: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Thief(hazardName, THIEF, hazardHint, eventDescriptions, isRoaming, isLiving);

					hazards.addHazard(newHazard);

					int startRoom = findRandomEmptyRoom();
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}

				break; 
			}
				
			case RAIDERS: {
				// create required extra variables
				int damage = (difficulty + 1) * 3;

				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Raiders(hazardName, RAIDERS, hazardHint, eventDescriptions, isRoaming, isLiving, damage);

					hazards.addHazard(newHazard);

					int startRoom = findRandomEmptyRoom();
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break; 
			}
				
			case TRADER: {
				// create and place as many as necessary
				for (int i = 0; i < amount; i++) {
					Hazard* newHazard = new Trader(hazardName, TRADER, hazardHint, eventDescriptions, isRoaming, isLiving);

					hazards.addHazard(newHazard);

					int startRoom = findRandomEmptyRoom();
					hazards.getLastHazard()->setStartingRoom(ruinRooms, startRoom);
				}
				break; 
			}
				
			case KNIGHT: {
				hazardData = loadFileAsVector(KNIGHT_DATA_PATH);
				break; 
			}

			default:
				cout << " The hazard could not be initialised \n";
		}
	}
}


int findRandomEmptyRoom() {
	// finds and returns a random room that does not have 
	// a hazard or player in it

	int room = rand() % TOTAL_ROOMS;

	while (ruinRooms[room]->hasHazard() || ruinRooms[room]->isPlayerInRoom()) {
		room = rand() % TOTAL_ROOMS;
	}

	return room;
}


int findEmptyAdjRoom(int currentRoom) {
	// returns the next available room a hazard can enter

	int room = -1;
	vector<int> availbleRooms;

	vector<int> connectedRooms = ruinRooms[currentRoom]->getExitConnections();
	vector<int>::const_iterator iter;

	for (iter = connectedRooms.begin(); iter != connectedRooms.end(); iter++) {
		int roomTemp = *iter;

		if (!ruinRooms[roomTemp]->hasHazard() || roomTemp == hazards.getHazard("Arigamo")->getCurrentRoom()) {
			availbleRooms.push_back(roomTemp);
		}
	}

	if (!availbleRooms.empty()) {
		room = availbleRooms[rand() % availbleRooms.size()];
	}

	return room;
}


void updateHazards(){
	// updates the game's hazards before the player's turn

	if (!player.isDisplaced() && totalTurns > 1) {
		moveHazards();
	}

	// updating interactions
	vector<string> eventTemp;

	Arigamo* arigamo = dynamic_cast<Arigamo*>(hazards.getHazard("Arigamo"));

	eventTemp = arigamo->drainPlayerHP((int*)roomConnections, TOTAL_ROOMS, player);
	eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
	
	// check arigamo interactions with player
	if (arigamo->getCurrentRoom() == player.getCurrentRoom()) {
		eventTemp = arigamo->updateInteraction(player);
		eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
	}

	// check arigamo interactions with other hazards in the same room
	if (ruinRooms[arigamo->getCurrentRoom()]->hasHazard()) {
		vector<int> hazardsInRoom = ruinRooms[arigamo->getCurrentRoom()]->getHazards();
		vector<int>::const_iterator iter;

		for (iter = hazardsInRoom.begin(); iter != hazardsInRoom.end(); iter++) {
			int hazID = *iter;

			if (hazID != arigamo->getID()) {
				eventTemp = arigamo->updateInteraction(hazards.getHazard(hazID));
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
			}
		}
	}

	// check other hazards interaction with the player
	vector<int> hazardsInRoom = ruinRooms[player.getCurrentRoom()]->getHazards();
	vector<int>::const_iterator iter;

	for (iter = hazardsInRoom.begin(); iter != hazardsInRoom.end(); iter++) {
		int hazID = *iter;
		Hazard* hazTemp = hazards.getHazard(hazID);

		switch (hazTemp->getType()) {
			case PIT: 
				eventTemp = dynamic_cast<Pit*>(hazTemp)->updateInteraction(player);
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
				break;
			
			case CCRAT: 
				eventTemp = dynamic_cast<CCRats*>(hazTemp)->updateInteraction(player, ruinRooms);
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
				break;
			
			case ORACLE: 
				eventTemp = dynamic_cast<Oracle*>(hazTemp)->updateInteraction(player);
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
				break;
			
			case THIEF: 
				eventTemp = dynamic_cast<Thief*>(hazTemp)->updateInteraction(player, ruinRooms);
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
				break;
			
			case RAIDERS: 
				eventTemp = dynamic_cast<Raiders*>(hazTemp)->updateInteraction(player, ruinRooms);
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
				break;
			
			case TRADER: 
				eventTemp = dynamic_cast<Trader*>(hazTemp)->updateInteraction(player, ruinRooms);
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
				break;
			
			case KNIGHT: 
				//eventTemp = dynamic_cast<Knight*>(hazTemp)->updateInteraction(player);
				eventQueue.insert(eventQueue.end(), eventTemp.begin(), eventTemp.end());
				break;
			
			default:
				cout << " There is no Hazard interaction with the player.\n";
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
			vector<int> connectedRooms = ruinRooms[arigamo->getCurrentRoom()]->getExitConnections();
			int nextRoom = connectedRooms[rand() % connectedRooms.size()];

			arigamo->moveTo(ruinRooms, nextRoom);

			arigamo->resetTurnsToWake();
			arigamo->setIsAsleep(true);
			eventQueue.push_back(arigamo->getEventDescriptions()[4]);

		}
	}
		
	// move other hazards
	vector<Hazard*>::const_iterator iter;
	vector<Hazard*> hazardsTemp = *hazards.getHazardsVector();

	for (iter = hazardsTemp.begin() + 1; iter != hazardsTemp.end(); iter++) {
		if ((*iter)->isRoaming() && !(*iter)->hasDied()) {
			bool willMove = rand() % 2;

			if (willMove) {
				int nextRoom = findEmptyAdjRoom((*iter)->getCurrentRoom());

				if (nextRoom != -1) {
					(*iter)->moveTo(ruinRooms, nextRoom);
				}
			}
		}
	}
}




//-------------------------------------//
// event management functions          //
//-------------------------------------//

//void updateEventQueue(vector<string> events){}


void clearEventQueue(){
	// clears the event queue
	eventQueue.clear();
}



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


	// need to check if arigamo is dead and player is in same room and player does not have gem


	return false;

}


//int calculatePlayerScore(){}