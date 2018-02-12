#include ".././Tiles/Fingerprint.h"
#include ".././Tiles//ComputerRoomF.h"

Fingerprint::~Fingerprint()
{
}


void Fingerprint::enter(PlayerInterface * player) {
	Tile::enter(player);
	if (player->getCharacter() == HACKER)
		hackerHere = true;
	if(!hackerHere && !player->has(MIRROR))
		setAlarm(true);
}

vector<string> Fingerprint::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if (computerRoom->getHackTokens() > 0 && hasAlarm())
		actions.push_back("USE_TOKEN");		// if you have an action, you can use a token to turn off the alarm
	
	return actions;
}

bool Fingerprint::doAction(string action, PlayerInterface * player) 
{
	if (action == toString(USE_TOKEN))
	{
		if (computerRoom->getHackTokens() > 0)
		{
			computerRoom->removeToken();
			setAlarm(false);
			player->newAction(toString(USE_TOKEN), getPos(),INT_MAX);
			DEBUG_MSG("You used a HACK_TOKEN to turn off the alarm");
			return true;
		}
		
	}
	return false;
}

void Fingerprint::exit(PlayerInterface * player) {
	if (player->getCharacter() == HACKER)
		hackerHere = false;
}