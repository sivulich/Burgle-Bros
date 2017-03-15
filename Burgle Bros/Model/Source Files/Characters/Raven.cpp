#include "../../Header Files/Characters/Raven.h"

string Raven::getAction(PlayerInterface * player)
{
	//if (player->currentTurn() != lastTurnUsed())
	{
		//setLastTurnUsed(player->currentTurn());
		return "CREATE_ALARM";
	}
	//else
		return "";
}
