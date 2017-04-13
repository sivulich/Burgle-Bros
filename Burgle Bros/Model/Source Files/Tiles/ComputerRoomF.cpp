#include "../../Header Files/Tiles/ComputerRoomF.h"


ComputerRoomF::~ComputerRoomF()
{
}

vector<string> ComputerRoomF::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	actions.push_back(toString(ADD_TOKEN));
	return actions;
}


void ComputerRoomF::doAction(string action, PlayerInterface * player) {
	if (action == toString(ADD_TOKEN)) {
		player->removeActionToken();
		addToken();
		DEBUG_MSG("You added a token to " << getPos());
	}
}
