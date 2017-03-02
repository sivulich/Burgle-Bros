#include "../../Header Files/Tiles/ComputerRoomM.h"


ComputerRoomM::~ComputerRoomM()
{
}

vector<string> ComputerRoomM::getActions(PlayerInterface * player)
{
	
	vector<string> actions(Tile::getActions(player));

	if ((player->getPosition() == getPos()) && player->getActionTokens() > 0)	// if the player is on this tile, allow him to put a hack token
		actions.push_back(toString(ADD_TOKEN));
	return actions;
}



void ComputerRoomM::doAction(string action, PlayerInterface * player) {
	if (action == toString(ADD_TOKEN)) {
		addToken();
		DEBUG_MSG("You added a token to " << getPos());
	}
}
