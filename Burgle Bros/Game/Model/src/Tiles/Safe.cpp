#include ".././Tiles/Safe.h"


Safe::~Safe()
{
}

vector<string> Safe::getActions(PlayerInterface * player) 
{
	vector<string> actions(Tile::getActions(player));
	if (safeIsOpen() == false)		
	{		
		if (tokens < 6 && player->getActionTokens() >= 2)
			actions.push_back("ADD_TOKEN");
		if (tokens > 0 && player->getActionTokens() >= 1)
			actions.push_back("THROW_DICE");
	}
	return actions;
}

bool Safe::doAction(string action, PlayerInterface * player) 
{
	if (action == "ADD_TOKEN")
	{
		player->removeActionToken();
		player->removeActionToken();
		addToken();
		player->newAction("ADD_TOKEN", getPos());
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
				DEBUG_MSG("You cracked the safe!!");
				player->addLoot(safeLoot);
				player->newAction("SAFE_OPENED", getPos());
			}
		}
	}
	////////////////// HACER BIEN RETURN VALUE
	return true;

}

void Safe::trySafeNumber(int number) {
	if (combinationTiles.size() != 0) 
	{
		vector<Tile *>::iterator pbegin = combinationTiles.begin();
		vector<Tile *>::iterator pend = combinationTiles.end();


		combinationTiles.erase(remove_if(pbegin, pend, [&](Tile * t) { return canCrack(t, number); }), combinationTiles.end());

		DEBUG_LN_MSG("Tiles remaining to crack: ");
			for (auto i : combinationTiles)
				DEBUG_LN_MSG(i->getPos() << " - ");
			DEBUG_MSG(endl);
		
	}
}

// if getSafeNumber equals diceThrown, then the tile will be cracked for the tile will always be uncracked when it arrives here
// and getSafeNumber returns a 0 if the tile is flipped down
bool Safe::canCrack( Tile * t, int dice) {	
	if (t->getSafeNumber() == dice)		// check if the tile can be cracked
	{
		t->crackTile();
		DEBUG_MSG("You cracked tile " << t->getPos());
		return true;
	}
	else
		return false;
}
