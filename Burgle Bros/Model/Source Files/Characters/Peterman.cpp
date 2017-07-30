#include "../../Header Files/Characters/Peterman.h"

Peterman::~Peterman()
{
}

string Peterman::getAction(PlayerInterface * player)
{
	if (true == canUseAbility())
	{
		return string("CREATE_ALARM");
	}
	else
		return string("");
}
