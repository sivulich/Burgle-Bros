#include "../../Header Files/Tiles/ComputerRoomF.h"


ComputerRoomF::~ComputerRoomF()
{
}

vector<string>& ComputerRoomF::getActions(PlayerInterface * player) {
	
	vector<string> posible;
	if ( (player->getPosition() == getPos()) && player->getActionTokens() > 0)	// if the player is on this tile, allow him to put a hack token
			posible.push_back(toString(ADD_TOKEN));
	return posible;
}


void ComputerRoomF::doAction(string action, PlayerInterface * player) {
	if (action == toString(ADD_TOKEN))
		addToken();
}
