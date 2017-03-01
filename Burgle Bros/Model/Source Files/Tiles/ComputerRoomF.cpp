#include "../../Header Files/Tiles/ComputerRoomF.h"


ComputerRoomF::~ComputerRoomF()
{
}

vector<string> ComputerRoomF::getActions(PlayerInterface * player)
{
	
	vector<string> actions(Tile::getActions(player));
	if ( (player->getPosition() == getPos()) && player->getActionTokens() > 0)	// if the player is on this tile, allow him to put a hack token
			actions.push_back(toString(ADD_TOKEN));
	return actions;
}


void ComputerRoomF::doAction(string action, PlayerInterface * player) {
	if (action == toString(ADD_TOKEN))
		addToken();
}
