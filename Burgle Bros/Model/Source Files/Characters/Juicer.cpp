#include "../../Header Files/Characters/Juicer.h"

string Juicer::getAction(PlayerInterface * player)
{
	if (player->currentTurn() != lastTurnUsed())
	{
		return "CREATE_ALARM";
	}
	else
		return "";
}
