#include ".././Tiles/Motion.h"
#include ".././Tiles/ComputerRoomM.h"


Motion::~Motion()
{
}


void Motion::enter(PlayerInterface * player) {
	Tile::enter(player);
	if (player->getCharacter() == HACKER)
		hackerHere = true;
	if(!hackerHere)
	arm();
}

void Motion::exit(PlayerInterface * player) {
	if (player->getCharacter() == HACKER)
		hackerHere = false;
	if (isArmed() )
	{
		setAlarm(true);
		disarm();
	}
}

vector<string> Motion::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));

	if (isArmed() && computerRoom->getHackTokens() > 0)
		actions.push_back("USE_TOKEN");		// if you have an action, you can use a token to disarm the system
	return actions;
}

bool Motion::doAction(string action, PlayerInterface * player)
{	
	if (action == "USE_TOKEN")
	{
		if (computerRoom->getHackTokens() > 0)
		{
			computerRoom->removeToken();

			disarm();
			setAlarm(false);
			player->newAction(toString(USE_TOKEN), getPos());
			return true;
		}
		
	}
	return false;
}
