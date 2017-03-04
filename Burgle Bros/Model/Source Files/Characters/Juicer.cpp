#include "../../Header Files/Characters/Juicer.h"

Juicer::~Juicer()
{
	lastTurnUsed = INT_MAX;
}

string Juicer::getAction(PlayerInterface * player)
{
	if (player->currentTurn() != lastTurnUsed)
	{
		lastTurnUsed = player-> currentTurn();
		return "CREATE_ALARM";
	}
	else
		return "";
}
