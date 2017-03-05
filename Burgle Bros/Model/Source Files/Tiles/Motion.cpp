#include "../../Header Files/Tiles/Motion.h"
#include "../../Header Files/Tiles/ComputerRoomM.h"


Motion::~Motion()
{
}


void Motion::enterTile(PlayerInterface * player) {
	Tile::enterTile(player);
	if (player->getCharacterType() == HACKER)
	{
		hackerhere = true;
		disarm();
	}
	else  if (hackerhere) disarm(); else arm();
}

void Motion::exitTile(PlayerInterface * player) {
	if (!hackerhere)
	{
		if (isArmed()) {
			setAlarm(true);
			disarm();
		}
	}
	else if (player->getCharacterType() == HACKER) hackerhere = false;
}

vector<string> Motion::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));

	if (myComputerRoom->getHackTokens() > 0)
		actions.push_back(toString(USE_TOKEN));		// if you have an action, you can use a token to disarm the system
	return actions;
}

void Motion::doAction(string action, PlayerInterface * player) {
	
	if (player->getActionTokens() > 0 && action == toString(USE_TOKEN)) {
		((ComputerRoomM *)myComputerRoom)->removeToken();
		disarm();
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
	}
}
