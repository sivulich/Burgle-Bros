#include ".././Tiles/ComputerRoomM.h"


ComputerRoomM::~ComputerRoomM()
{
}

vector<string> ComputerRoomM::getActions(PlayerInterface * player)
{	
	vector<string> actions(Tile::getActions(player));
	actions.push_back("ADD_TOKEN");
	return actions;
}



bool ComputerRoomM::doAction(string action, PlayerInterface * player) {
	if (action == "ADD_TOKEN") {
		if (hackToken < 6)
		{
			player->removeActionToken();
			addToken();
			return true;
		}
		DEBUG_MSG("You added a token to " << getPos());
	}
	return false;
}
