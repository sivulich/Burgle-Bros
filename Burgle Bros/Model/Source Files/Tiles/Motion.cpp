#include "../../Header Files/Tiles/Motion.h"


Motion::~Motion()
{
}


void Motion::enterTile(void * player) {
	arm();
}

vector<string>& Motion::getActions(void * player) {
	Player * p = (Player *)player;

	vector<string> actions;
	if (p->getActionTokens() > 0)
		actions.push_back(toString(USE_TOKEN));		// if you have an action, you can use a token to disarm the system
}

void Motion::doAction(string action, void * player) {
	Player * p = (Player *)player;

	if (p->getActionTokens() > 0 && action == toString(USE_TOKEN)) {
		disarm();		/////////////////// TAMBIEN TIENE QUE APAGAR LA ALARMA SI HAY ALGUNA?????
		p->newAction(toString(USE_TOKEN), getPos());
	}
}
