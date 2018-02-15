#include ".././Tiles/Safe.h"


Safe::~Safe()
{
}

void Safe::enter(PlayerInterface * player)
{
	Tile::enter(player);
	if (player->has(KEYCARD))
		keyCardHere = true;
}

void Safe::exit(PlayerInterface * player)
{
	if (player->has(KEYCARD))
		keyCardHere = false;
}

vector<string> Safe::getActions(PlayerInterface * player)
{
	int b = (player->getCharacter() == PETERMAN) ? 1 : 0;
	vector<string> actions(Tile::getActions(player));
	if (safeIsOpen() == false)
	{
		if (dices < 6 && player->getActionTokens() >= 2)
			actions.push_back("ADD_DIE");
		if ((dices + b) > 0 && player->getActionTokens() >= 1 && keyCardHere)
			actions.push_back("CRACK_SAFE");
	}
	return actions;
}

bool Safe::doAction(string action, PlayerInterface * player)// Bool endThrow return value has different meanings depending on the action realized in the tile
{															// If adding a token, true means that the token was added correctly, false meaning otherwise
	bool endThrow = false;									// If throwing die, true means that all throws done during the current action are done, false meaning that more dies are waiting to be thrown.
	int b = (player->getCharacter() == PETERMAN) ? 1 : 0;
	if (action == "ADD_TOKEN" && player->getActionTokens() >= 2 && dices < 6)
	{
		player->removeActionToken();
		player->removeActionToken();
		addDice();
		player->newAction("ADD_TOKEN", getPos(), INT_MAX);
		endThrow = true;
		DEBUG_MSG("You added a new die to this safe. You can now throw " << dices << " dices.");
	}
	else if (action == "THROW_DICE" && keyCardHere)
	{
		if (dicesThisTurn < (dices + b) && !safeIsOpen())// while the safe remains closed, throw all the dice you have
		{
			if (dicesThisTurn == 0)
				player->removeActionToken();// remove an action
			trySafeNumber(player->getDice());// check how many tiles you cracked throwing one die
			dicesThisTurn++;

			if (combinationTiles.size() == 0)//  if the vector is empty, then all the tiles were cracked
			{
				endThrow = true;
				safeCracked = true;	// if so, you opened the safe
				DEBUG_MSG("You cracked the safe!!");
				player->addLoot(safeLoot);
				player->newAction("SAFE_OPENED", getPos(), INT_MAX);
				if (safeLoot == CURSED_GOBLET && player->getActionTokens() > 0)
					player->removeStealthToken();
				if (safeLoot == KEYCARD)
				{
					for (auto &it : otherSafes)
						((Safe *)it)->isKeyCardHere(false);
				}
				if (safeLoot == GOLD_BAR)
				{
					Tile::setLoot(LootFactory().newLoot(GOLD_BAR));
				}
				notify();
			}
			if (dicesThisTurn == (dices + b) && !safeIsOpen())
			{
				dicesThisTurn = 0;
				endThrow = true;
			}

		}
		else endThrow = true;
	}
	return endThrow;

}

void Safe::trySafeNumber(int number) {
	cout << "Threw a " << number << endl;
	vector <Tile *> v;
	if (combinationTiles.size() != 0)
	{
		for (auto &it : combinationTiles)
		{
			if (it->isFlipped() && it->getSafeNumber() == number)
				it->crackTile();
			else v.push_back(it);
		}
		combinationTiles = v;
		DEBUG_LN_MSG("Tiles remaining to crack: ");
		for (auto i : combinationTiles)
			DEBUG_LN_MSG(i->getPos() << " - ");
		DEBUG_MSG(endl);

	}
}

// if getSafeNumber equals diceThrown, then the tile will be cracked for the tile will always be uncracked when it arrives here
// and getSafeNumber returns a 0 if the tile is flipped down
bool Safe::canCrack(Tile * t, int dice) {
	if (t->getSafeNumber() == dice)		// check if the tile can be cracked
	{
		t->crackTile();
		DEBUG_MSG("You cracked tile " << t->getPos());
		return true;
	}
	else
		return false;
}
