#include ".././Tiles/ComputerRoomF.h"


ComputerRoomF::~ComputerRoomF()
{
}

vector<string> ComputerRoomF::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if(hackToken <= 5)
	actions.push_back("ADD_TOKEN");
	return actions;
}


bool ComputerRoomF::doAction(string action, PlayerInterface * player) 
{
	bool b = false;
	if (action == "ADD_TOKEN")
	{
		if (hackToken < 6)
		{
			player->removeActionToken();
			addToken();
			b = true;
		}

		DEBUG_MSG("You added a token to " << getPos());
	}
	return b;
}