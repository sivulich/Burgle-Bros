#include ".././Characters/Spotter.h"


string Spotter::getAction(PlayerInterface * player) 
{
	if (true == canUseAbility())
	{
		return "SPY_PATROL";
	}
	else
		return "";
}