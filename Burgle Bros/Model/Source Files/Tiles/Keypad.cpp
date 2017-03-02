#include "../../Header Files/Tiles/Keypad.h"


Keypad::~Keypad()
{
}

bool Keypad::canMove(PlayerInterface * player) {
	
	if (keyKnown == false)
	{
		for (int i = 0; i < attemptsThisTurn + 1 && keyKnown == false; i++)		// throw the dice attempts+1 times 
		{
			if (player->throwDice() == 6) { 	// if the die thrown equals six
				keyKnown = true;		// you may enter the tile
				DEBUG_MSG("You managed to hack the keypad. Now you can enter freely.");
			}
			else
				DEBUG_MSG("You threw the dice but you couldn't open the keypad.");

			player->newAction(toString(THROW_DICE), getPos());	// tell the player what you did
		}
		if (keyKnown == false) addAttempt();		// if you didnt open the keypad, increase the attempts made this turn
	}
	return keyKnown;
}


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
				enterTile(p);
			}
		}
		else		// if the tile is flipped up and you could MOVE, then you know the key
		{
			p.removeActionToken();
			enterTile(p);
		}	
	}
	else if (action == toString(THROW_DICE))
	{
		p.removeActionToken();
		
	}
}
*/