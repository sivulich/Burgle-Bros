#include "../../Header Files/Tiles/ComputerRoomL.h"


ComputerRoomL::~ComputerRoomL()
{
}

vector<string>& ComputerRoomL::getActions(void * player) {
	Player * p = (Player *)player;
	vector<string> posible;
	if ((p->getPosition() == getPos()) && p->getActionTokens() > 0)	// if the player is on this tile, allow him to put a hack token
		posible.push_back(toString(ADD_TOKEN));
}


void ComputerRoomL::doAction(string action, void * player) {
	if (action == toString(ADD_TOKEN))
		addToken();
}