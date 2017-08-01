#include ".././Characters/Juicer.h"

string Juicer::getAction(PlayerInterface * player)
{
	if (true == canUseAbility())
	{
		return string("CREATE_ALARM");
	}
	else
		return string("");
}
