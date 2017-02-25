#include "../../Header Files/Tiles/ComputerRoomM.h"


ComputerRoomM::~ComputerRoomM()
{
}

vector<string>& ComputerRoomM::getActions(PlayerInterface * player) {
	
	vector<string> posible;
	if ((player->getPosition() == getPos()) && player->getActionTokens() > 0)	// if the player is on this tile, allow him to put a hack token
		posible.push_back(toString(ADD_TOKEN));
	return posible;
}



void ComputerRoomM::doAction(string action, PlayerInterface * player) {
	if (action == toString(ADD_TOKEN))
		addToken();
}
