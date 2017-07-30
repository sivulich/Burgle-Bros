#include "../../Header Files/Characters/Acrobat.h"

Acrobat::~Acrobat()
{
}

string Acrobat::getAction(PlayerInterface * player)
{
	if (true == canUseAbility())
	{
		return string("CREATE_ALARM");
	}
	else
		return string("");
}
