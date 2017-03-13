#include "../../Header Files/Tiles/Laser.h"
#include "../../Header Files/Tiles/ComputerRoomL.h"



Laser::~Laser()
{
}

void Laser::enter(PlayerInterface * player) 
{
	Tile::enter(player);
	setAlarm(true);
}

vector<string> Laser::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if (computerRoom->getHackTokens() > 0)
		actions.push_back("USE_TOKEN");		// you can use an extra action to turn off the alarm
	return actions;
}

void Laser::doAction(string action, PlayerInterface * player)
{
	

	if (action == "SPENT_OK")
	{
		player->removeActionToken();		
		player->removeActionToken();
		setAlarm(false);
		player->newAction(toString(SPENT_OK), getPos());
		DEBUG_MSG("You decided to use two action tokens to turn off the alarm.");
	}
	else if (action == "USE_TOKEN")
	{
		computerRoom->removeToken();
		setAlarm(false);
		player->newAction(toString(USE_TOKEN), getPos());
	}
}