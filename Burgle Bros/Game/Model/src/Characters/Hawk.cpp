#include ".././Characters/Hawk.h"

Hawk::~Hawk()
{
}

string Hawk::getAction(PlayerInterface * player)
{
	if (true == canUseAbility())
	{
		return string("");
	}
	else
		return string("");
}
