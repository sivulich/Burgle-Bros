#include ".././Tiles/Deadbolt.h"


Deadbolt::~Deadbolt()
{
}

bool Deadbolt::canMove(PlayerInterface * player)
{
	// If tile is revealed but player has less than three tokens, cant move
	if (isFlipped()==true && player->getActionTokens() < 3)
		return false;
	else
		return true;
}

void Deadbolt::enter(PlayerInterface * player)
{
	// If player has enough action tokens enter the tile
	if (player->getActionTokens() >= 3)
	{
		Tile::enter(player);
		player->removeActionToken();
		player->removeActionToken();
		player->removeActionToken();
		DEBUG_MSG("You spent three actions to enter the deadbolt");
	}
	else
		cout << "UNEXPECTED ERROR IN DEADBOLT." << endl;
}

/*
vector<string>& Deadbolt::getActions(Player p, Coord guardPos, Coord partnerPos) {
	actions.clear();

	if (isAdjacent(p.getPosition())) {
		if (canPeek(p) == true)
			actions.push_back(toString(PEEK));
		if (isFlipped() == false)		//if the card is flipped down
		{		
			if (p.getActionTokens() > 0)		//and the player has an action token
				actions.push_back(toString(MOVE));
		}
		else	//the tile is flipped up
		{
			if (((guardPos == getPos()) || (partnerPos == getPos())) && p.getActionTokens() > 0)	//if the player or the guard is on this tile and the player has at least 1 action token
				actions.push_back(toString(MOVE));
			else if (p.getActionTokens() >= 3)	//if the tile is empty and the player has 3 or more action tokens
				actions.push_back(toString(MOVE));
		}
		
	}
}

void Deadbolt::doAction(string action, Player p, Coord guardPos, Coord partnerPos) {
	if (action == toString(PEEK))
		Tile::peek(p);
	else if (action == toString(MOVE)) {
		if (isFlipped() == false)		//if the tile is flipped down
		{
			if (p.getActionTokens() < 3)
			{
				turnUp();
				DEBUG_MSG("This is a Deadbolt and you dont have enough action tokens to move here.");
				p.removeActionToken();
				addPlayerAction(p, toString(MOVE));
			}
			else
			{
				turnUp();
				DEBUG_MSG("You used 3 action tokens to enter the deadbolt.");
				p.removeActionToken();		//remove 3 action tokens
				p.removeActionToken();
				p.removeActionToken();
				enter(p);
			}
		}
		else		//the tile is flipped up
		{
			if ((guardPos == getPos()) || (partnerPos == getPos())) {	//if someone is on the tile
				p.removeActionToken();
				enter(p);
			}
			else	//the tile is empty
			{
				DEBUG_MSG("You used 3 action tokens to enter the deadbolt.");
				p.removeActionToken();		//remove 3 action tokens
				p.removeActionToken();
				p.removeActionToken();
				enter(p);
			}
		}
	}
}
*/
