#include "../../Header Files/Tiles/Fingerprint.h"

Fingerprint::~Fingerprint()
{
}


void Fingerprint::enterTile(PlayerInterface * player) {
	Tile::enterTile(player);
	setAlarm(true);
}

vector<string> Fingerprint::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if (myComputerRoom->getHackTokens() > 0)
		actions.push_back(toString(USE_TOKEN));		// if you have an action, you can use a token to turn off the alarm
	
	return actions;
}

void Fingerprint::doAction(string action, PlayerInterface * player) 
{
	if (action == toString(USE_TOKEN)) {
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
		DEBUG_MSG("You used a HACK_TOKEN to turn off the alarm");
	}
}
