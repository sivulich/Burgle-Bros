#include ".././Characters/Hawk.h"

Hawk::~Hawk()
{
}

string Hawk::getAction(PlayerInterface * player)
{
	if (true == canUseAbility())
	{
		return string("CREATE_ALARM");
	}
	else
		return string("");
}
