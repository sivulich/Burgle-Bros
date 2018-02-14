#include ".././Tiles/Laser.h"
#include ".././Tiles/ComputerRoomL.h"



Laser::~Laser()
{
}

void Laser::enter(PlayerInterface * player) 
{
	Tile::enter(player);
	if (player->getCharacter() == HACKER)
		hackerHere = true;
	if (!hackerHere)
	{
		setAlarm(true);
	}
	
}

vector<string> Laser::getActions(PlayerInterface * player)
{
	vector<string> actions(Tile::getActions(player));
	if (computerRoom->getHackTokens() > 0 && this->hasAlarm())
		actions.push_back("USE_TOKEN");		// you can use an extra action to turn off the alarm
	return actions;
}

bool Laser::doAction(string action, PlayerInterface * player)
{
	if (hackerHere==false && !player->has(MIRROR))
	{
		if (action == "SPENT_OK")
		{
			if (isFlipped() == false)
			{
				player->removeActionToken(),
				turnUp();
			}
			player->removeActionToken();
			setAlarm(false);
			player->newAction(toString(SPENT_OK), getPos(),INT_MAX);
			DEBUG_MSG("You decided to use action tokens to turn off the alarm.");
		}
		else if (action == "USE_TOKEN")
		{
			computerRoom->removeToken();
			setAlarm(false);
			player->newAction(toString(USE_TOKEN), getPos(),INT_MAX);
		}
	}
	////////////////// HACER BIEN RETURN VALUE
	return true;
}

void Laser::exit(PlayerInterface * player) {
	if (player->getCharacter() == HACKER)
		hackerHere = false;
}