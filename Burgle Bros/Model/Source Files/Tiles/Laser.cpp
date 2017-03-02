#include "../../Header Files/Tiles/Laser.h"


Laser::~Laser()
{
}

void Laser::enterTile(PlayerInterface * player) 
{
	Tile::enterTile(player);
	setAlarm(true);
}

vector<string> Laser::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if (player->getActionTokens() > 0)
		actions.push_back("USE_TOKEN");		// you can use an extra action to turn off the alarm
	return actions;
}

void Laser::doAction(string action, PlayerInterface * player) {
	

	if (action == toString(SPENT_OK)) {		// remove two action tokens and turn off the alarm
		player->removeActionToken();		
		player->removeActionToken();
		setAlarm(false);
		player->newAction(toString(SPENT_OK), getPos());
		DEBUG_MSG("You decided to use two action tokens to turn off the alarm.");
	}
	else if (action == toString(USE_TOKEN)) {
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
	}
}