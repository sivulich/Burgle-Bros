#include "../../Header Files/Tiles/Fingerprint.h"
#include "../../Header Files/Tiles//ComputerRoomF.h"

Fingerprint::~Fingerprint()
{
}


void Fingerprint::enter(PlayerInterface * player) {
	Tile::enter(player);
	if (player->getCharacterType() == HACKER)
		hackerhere = true;
	if(!hackerhere)
	setAlarm(true);
}

vector<string> Fingerprint::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if (computerRoom->getHackTokens() > 0 && hasAlarm())
		actions.push_back("USE_TOKEN");		// if you have an action, you can use a token to turn off the alarm
	
	return actions;
}

void Fingerprint::doAction(string action, PlayerInterface * player) 
{
	if (action == toString(USE_TOKEN)) {
		computerRoom->removeToken();
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
		DEBUG_MSG("You used a HACK_TOKEN to turn off the alarm");
	}
}

void Fingerprint::exit(PlayerInterface * player) {
	if (player->getCharacterType() == HACKER)
		hackerhere = false;
}