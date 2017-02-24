#include "../../Header Files/Tiles/Laser.h"


Laser::~Laser()
{
}

void Laser::enterTile(void * player) {
	setAlarm(true);
}

vector<string>& Laser::getActions(void * player) {
	Player * p = (Player *)player;

	vector<string> actions;
	if (p->getActionTokens() > 0)
		actions.push_back(toString(USE_TOKEN));		// you can use an extra action to turn off the alarm
}

void Laser::doAction(string action, void * player) {
	Player * p = (Player *)player;

	if (action == toString(SPENT_OK)) {		// remove two action tokens and turn off the alarm
		p->removeActionToken();		
		p->removeActionToken();
		setAlarm(false);
		p->newAction(toString(SPENT_OK), getPos());
		DEBUG_MSG("You decided to use two action tokens to turn off the alarm.");
	}
	else if (action == toString(USE_TOKEN)) {
		setAlarm(false);
		p->newAction(toString(USE_TOKEN), getPos());
	}
}