#include "../../Header Files/Tiles/ComputerRoomM.h"


ComputerRoomM::~ComputerRoomM()
{
}

vector<string> ComputerRoomM::getActions(PlayerInterface * player)
{	
	vector<string> actions(Tile::getActions(player));
	actions.push_back(toString(ADD_TOKEN));
	return actions;
}



void ComputerRoomM::doAction(string action, PlayerInterface * player) {
	if (action == toString(ADD_TOKEN)) {
		player->removeActionToken();
		addToken();
		DEBUG_MSG("You added a token to " << getPos());
	}
}
