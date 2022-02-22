_________________________________________________________________________
Project: The Tamer, the Arigamo and the Fuhai Gem
Task: FIT1048 Assignment 2 + 3
Author: Sean Lee

These are some additional details relating to the current version of the assignment.
_________________________________________________________________________

	- If you are having issues with the game running, try commenting out 'setWindowSize()' in the 'gameSetUp()' function within 'Application.cpp'


Changes in names that deviate from the specifications:
	- Wumpus -> Arigamo
	- Bats -> Colony of Corrupted Rats (CCRats)


How to win: (must fulfil both conditions - this is also stated in the second paragraph of the 'How To Play' screen)
	- Kill the Arigamo with your Crossbow by shooting it
	- Retrieve the Fuhai Gem from the dead Arigamo (ensure it does not get taken by a roaming opponent before you)


How to see Hazard details during the game:
	- Uncomment the last cout statement in the 'displayUI()' function within 'Application.cpp'


Additional functionality implemented:
	- Difficulty levels (Easy, Normal, Hard) which can be selected by player
	- Scoring system based on game parameters
	- Wumpus has a chance of moving after random number of turns
	- Custom theme and story
	- Magic crooked arrows which can be shot through 1-5 locations
	- 5 roaming opponents


Additional classes added since Assignment 2 that were not originally planned:
	- HazardContainer
	- RoomContainer
	- EventQueue

