#include "../../Header Files/Characters/Raven.h"

Raven::~Raven()
{
	lastTurnUsed = INT_MAX;
}

string Raven::getAction(PlayerInterface * player)
{
	if (player->currentTurn() != lastTurnUsed)
	{
		lastTurnUsed = player->currentTurn();
		return "CREATE_ALARM";
	}
	else
		return "";
}
