#include "../../Header Files/Tiles/Safe.h"


Safe::~Safe()
{
}

vector<string> Safe::getActions(PlayerInterface * player) 
{
	vector<string> actions(Tile::getActions(player));
	if (safeIsOpen() == false)		// if the safe is closed
	{		
		if (tokens < 6 && player->getActionTokens() >= 2)	actions.push_back(toString(ADD_TOKEN));
		if (tokens > 0 && player->getActionTokens() >= 1)	actions.push_back(toString(THROW_DICE));
	}
	return actions;
}

void Safe::doAction(string action, PlayerInterface * player) 
{
	if (action == "ADD_TOKEN")
	{
		player->removeActionToken();
		player->removeActionToken();
		addToken();
		player->newAction(toString(ADD_TOKEN), getPos());
		DEBUG_MSG("You added a new dice to this safe. You can now throw " << tokens << " dice.");
	}
	else if (action == "THROW_DICE")
	{
		player->removeActionToken();		// remove an action
		for (int i = 0; i < tokens && !safeIsOpen(); i++)		// while the safe remains closed, throw all the dice you have
		{
			trySafeNumber(player->throwDice());			// check how many tiles you cracked throwing one die

			if (combinationTiles.size() == 0) {		//  if the vector is empty, then all the tiles were cracked
				safeCracked = true;								// if so, you opened the safe
				player->newAction("SAFE_OPENED", getPos());
			}
		}
		DEBUG_MSG("You managed to crack " << (6-combinationTiles.size()) << " tiles so far.");
	}

}

void Safe::trySafeNumber(int number) {
	if (combinationTiles.size() != 0) 
	{
		vector<Tile *> tempTiles;
		for (vector<Tile *>::iterator it = combinationTiles.begin(); it != combinationTiles.end(); it++) 
			if (!canCrack(*it, number)) tempTiles.push_back(*it);		// if you can't crack them, place them in another vector

		combinationTiles = tempTiles;

		DEBUG_LN_MSG("Tiles remaining to crack: ");
			for (auto i : combinationTiles)
				DEBUG_LN_MSG(i->getPos() << " - ");
			DEBUG_MSG(endl);
		
	}
}

// if getSafeNumber equals diceThrown, then the tile will be cracked for the tile will always be uncracked when it arrives here
// and getSafeNumber returns a 0 if the tile is flipped down
bool Safe::canCrack(Tile * t, int number) {	
	if (t->getSafeNumber() == number)		// check if the tile can be cracked
	{
		t->crackTile();
		return true;
	}
	else
		return false;
}