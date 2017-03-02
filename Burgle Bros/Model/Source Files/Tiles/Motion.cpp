#include "../../Header Files/Tiles/Motion.h"


Motion::~Motion()
{
}


void Motion::enterTile(PlayerInterface * player) {
	Tile::enterTile(player);
	arm();
}

void Motion::exitTile(PlayerInterface * player) {
	if (isArmed()) {
		setAlarm(true);
		disarm();
	}
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
		disarm();		
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
	}
}
