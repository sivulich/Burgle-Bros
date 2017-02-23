#include "../../Header Files/Tiles/ComputerRoomM.h"


ComputerRoomM::~ComputerRoomM()
{
}

vector<string>& ComputerRoomM::getActions(void * player) {
	Player * p = (Player *)player;
	vector<string> posible;
	if ((p->getPosition() == getPos()) && p->getActionTokens() > 0)	// if the player is on this tile, allow him to put a hack token
		posible.push_back(toString(ADD_TOKEN));
}


void ComputerRoomM::doAction(string action, void * player) {
	if (action == toString(ADD_TOKEN))
		addToken();
}
