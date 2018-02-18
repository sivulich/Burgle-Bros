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
				notify();
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