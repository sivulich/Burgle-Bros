#include ".././Tiles/Deadbolt.h"


Deadbolt::~Deadbolt()
{
}



bool Deadbolt::doAction(string action, PlayerInterface * player)
{
	if (action == "SPENT_OK")
	{
		if (isFlipped() == false)
		{
			player->removeActionToken(),
			turnUp();
			DEBUG_MSG("Used 4 action tokens to enter Deadbolt.");
		}
		player->removeActionToken();
		player->removeActionToken();
		return true;
	}
	return false;
}


