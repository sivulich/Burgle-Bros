#include ".././Tiles/ComputerRoomF.h"


ComputerRoomF::~ComputerRoomF()
{
}

vector<string> ComputerRoomF::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if(hackToken <= 4)
	actions.push_back("ADD_TOKEN");
	return actions;
}


bool ComputerRoomF::doAction(string action, PlayerInterface * player) {
	if (action == "ADD_TOKEN") {
		if (hackToken<6) player->removeActionToken();
		addToken();
		DEBUG_MSG("You added a token to " << getPos());
	}
	////////////////// HACER BIEN RETURN VALUE
	return true;
}
