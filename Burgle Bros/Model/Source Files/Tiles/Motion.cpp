#include "../../Header Files/Tiles/Motion.h"


Motion::~Motion()
{
}


void Motion::enterTile(PlayerInterface * player) {
	arm();
}

vector<string>& Motion::getActions(PlayerInterface * player)
{
	vector<string> actions;
	if (player->getActionTokens() > 0)
		actions.push_back(toString(USE_TOKEN));		// if you have an action, you can use a token to disarm the system
	return actions;
}

void Motion::doAction(string action, PlayerInterface * player) {
	

	if (player->getActionTokens() > 0 && action == toString(USE_TOKEN)) {
		disarm();		/////////////////// TAMBIEN TIENE QUE APAGAR LA ALARMA SI HAY ALGUNA?????
		player->newAction(toString(USE_TOKEN), getPos());
	}
}
