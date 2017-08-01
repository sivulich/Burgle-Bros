#include ".././Characters/Raven.h"

string Raven::getAction(PlayerInterface * player)
{
	if (true == canUseAbility())
	{
		return "PLACE_CROW";
	}
	else
		return "";
}
