#include "../../Header Files/Tiles/Fingerprint.h"
#include "../../Header Files/Tiles//ComputerRoomF.h"

Fingerprint::~Fingerprint()
{
}


void Fingerprint::enterTile(PlayerInterface * player) {
	Tile::enterTile(player);
	if (player->getCharacterType() == HACKER) hackerhere = true;
	if(!hackerhere) setAlarm(true);
}

vector<string> Fingerprint::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if (myComputerRoom->getHackTokens() > 0 && hasAlarm())
		actions.push_back(toString(USE_TOKEN));		// if you have an action, you can use a token to turn off the alarm
	
	return actions;
}

void Fingerprint::doAction(string action, PlayerInterface * player) 
{
	if (action == toString(USE_TOKEN)) {
		((ComputerRoomF *)myComputerRoom)->removeToken();
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
		DEBUG_MSG("You used a HACK_TOKEN to turn off the alarm");
	}
}

void Fingerprint::exitTile(PlayerInterface * player) 
{
	if (player->getCharacterType() == HACKER) hackerhere = false;
}
