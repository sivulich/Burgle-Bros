#include "../../Header Files/Characters/Spotter.h"


Spotter::~Spotter()
{
	lastTurnUsed = INT_MAX;
}

string Spotter::getAction(PlayerInterface * player) 
{
	if (player->currentTurn() != lastTurnUsed)
	{
		lastTurnUsed = player->currentTurn();
		return "SPY_PATROL";
	}
	else
		return "";
}