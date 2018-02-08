#include ".././Tiles/Keypad.h"


Keypad::~Keypad()
{
}

bool Keypad::canMove(PlayerInterface * player)
{
	return keyKnown;
}

bool Keypad::tryToOpen(int dice, PlayerInterface * player)
{
	int b = (player->getCharacter() == PETERMAN) ? 1 : 0;
	player->newAction("THROW_DICE", this->getPos(), dice);
	bool endAction = false;
	if (currentPlayer == -1)
	{
		currentTurn = player->getTurn();
		currentPlayer = player->getNumber();
	}
	if (currentTurn == player->getTurn() && currentPlayer != player->getNumber())
	{
		currentPlayer = player->getNumber();
		clearAttempts();
	}
	if (currentTurn != player->getTurn())
	{
		currentTurn = player->getTurn();
		currentPlayer = player->getNumber();
		clearAttempts();
	}

	if (keyKnown == false)
	{
		if (isFlipped() == false)
			turnUp();
		if (attemptsThisAction < attemptsThisTurn + 1 + b)
		{
			if (dice == 6) { 	// if the die thrown equals six
				keyKnown = true;		// you may enter the tile
				DEBUG_MSG("You managed to hack the keypad. Now you can enter freely.");
				endAction = true;
			}
			else
				DEBUG_MSG("You threw the dice but you couldn't open the keypad.");
			player->newAction(toString(THROW_DICE), getPos(),dice);	// tell the player what you did
			attemptsThisAction++;

			if (attemptsThisAction == attemptsThisTurn + 1 + b && keyKnown == false)
			{
				addAttempt();
				attemptsThisAction = 0;
				endAction = true;
			}
		}
	}
	return endAction;
}
	/*
	for (int i = 0; (i < attemptsThisTurn + 1 + b) && keyKnown == false; i++)		// throw the dice attempts+1 times
	{
	if (dice == 6) { 	// if the die thrown equals six
	keyKnown = true;		// you may enter the tile
	DEBUG_MSG("You managed to hack the keypad. Now you can enter freely.");
	}
	else
	DEBUG_MSG("You threw the dice but you couldn't open the keypad.");

	player->newAction(toString(THROW_DICE), getPos());	// tell the player what you did
	}
	if (keyKnown == false) addAttempt();		// if you didnt open the keypad, increase the attempts made this turn
	}*/

/*
vector<string>& Keypad::getActions(Player p, Coord guardPos, Coord partnerPos)
{
	actions.clear();
	if (isAdjacent(p.getPosition())) 
	{
		if (canPeek(p))
			actions.push_back(toString(PEEK));

		if (p.getActionTokens() > 0) {			//if the player has at least one action
			if (isFlipped() == true && keyKnown == false)		// and the tile is up but the key is not known
				actions.push_back(toString(THROW_DICE));		// throw dice and move if you get a six
			else
				actions.push_back(toString(MOVE));
		}
	}
	return actions;
}

void Keypad::doAction(string action, Player p, Coord guardPos, Coord partnerPos) {

	if (action == toString(PEEK)) {
		p.removeActionToken();
		peek(p);
	}
	else if (action == toString(MOVE)) 
	{
		if (isFlipped() == false)		//if the tile is flipped down (ergo you dont know the key)
		{
			turnUp();					//flip the card
			p.removeActionToken();
			if (p.throwDice() == 6)		// then you can enter the tile
			{
				keyKnown = true;
				enter(p);
			}
		}
		else		// if the tile is flipped up and you could MOVE, then you know the key
		{
			p.removeActionToken();
			enter(p);
		}	
	}
	else if (action == toString(THROW_DICE))
	{
		p.removeActionToken();
		
	}
}
*/