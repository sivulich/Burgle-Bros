#include "../../Header Files/Characters/Spotter.h"


string Spotter::getAction(PlayerInterface * player) 
{
	if (player->currentTurn() != lastTurnUsed())
	{
		return "SPY_PATROL";
	}
	else
		return "";
}