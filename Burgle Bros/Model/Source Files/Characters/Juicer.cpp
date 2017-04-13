#include "../../Header Files/Characters/Juicer.h"

string Juicer::getAction(PlayerInterface * player)
{
	if (true == canUseAbility())
	{
		return "CREATE_ALARM";
	}
	else
		return "";
}
