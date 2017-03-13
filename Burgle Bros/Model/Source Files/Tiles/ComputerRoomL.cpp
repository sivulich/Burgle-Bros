#include "../../Header Files/Tiles/ComputerRoomL.h"


ComputerRoomL::~ComputerRoomL()
{
}

vector<string> ComputerRoomL::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	actions.push_back(toString(ADD_TOKEN));
	return actions;
}


void ComputerRoomL::doAction(string action, PlayerInterface * player) {
	if (action == toString(ADD_TOKEN)) {
		player->removeActionToken();
		addToken();
		DEBUG_MSG("You added a token to " << getPos());
	}
}