#include "../../Header Files/Tiles/Safe.h"


Safe::~Safe()
{
}

vector<string>& Safe::getActions(void * player) {
	Player * p = (Player *)player;

	if (safeIsOpen() == false)		// if the safe is closed
	{		
		vector<string> tempActions;
		if (tokens < 6 && p->getActionTokens() >= 2)	tempActions.push_back(toString(ADD_TOKEN));
		if (tokens > 0 && p->getActionTokens() >= 1)	tempActions.push_back(toString(THROW_DICE));
	}
}

void Safe::doAction(string action, void * player) {
	Player * p = (Player *)player;

	if (action == "ADD_TOKEN")
	{
		p->removeActionToken();
		p->removeActionToken();
		addToken();
		p->newAction(toString(ADD_TOKEN), getPos());
		DEBUG_MSG("You added a new dice to this safe.");
	}
	else if (action == "THROW_DICE")
	{
		p->removeActionToken();		// remove an action
		int tilesUCracked = 0;
		for (int i = 0; i < tokens && !safeIsOpen(); i++)		// while the safe remains closed, throw all the dice you have
		{
			tilesUCracked = trySafeNumber(p->throwDice());			// check how many tiles you cracked throwing one die	
			p->newAction(toString(THROW_DICE), getPos());			// tell the player what you did

			if ((tilesCracked += tilesUCracked) == 6) {		// add it to the already cracked tiles, and check if you got all of them
				cracked = true;								// if so, you opened the safe
				p->newAction("SAFE_OPENED", getPos());
			}
		}
		DEBUG_MSG("You managed to crack " << tilesCracked << " tiles so far.");
	}

}

int Safe::trySafeNumber(int number) {
	int retValue = 0;
	for (auto it = combination.begin(); it != combination.end(); ++it) {		// iterate through the array of combination numbers
		if (*it == number) {					// if it matches the number you tried, erase it from the vector
			combination.erase(it);
			++retValue;
		}
	}
	return retValue;
}
