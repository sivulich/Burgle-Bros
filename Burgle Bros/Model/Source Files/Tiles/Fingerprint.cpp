#include "../../Header Files/Tiles/Fingerprint.h"

Fingerprint::~Fingerprint()
{
}


void Fingerprint::enterTile(void * player) {
	Player * p = (Player *)player;
	setAlarm(true);
}

vector<string>& Fingerprint::getActions(void * player) {
	Player * p = (Player *)player;

	vector<string> actions;
	if (p->getActionTokens() > 0)
		actions.push_back(toString(USE_TOKEN));		// if you have an action, you can use a token to turn off the alarm
}

void Fingerprint::doAction(string action, void * player) {
	Player * p = (Player *)player;

	if (p->getActionTokens() > 0 && action == toString(USE_TOKEN)) {
		p->removeActionToken();
		setAlarm(false);
	}
}
