#include "../../Header Files/Tiles/Safe.h"


Safe::~Safe()
{
}

vector<string>& Safe::getActions(void * player) {
	Player * p = (Player *)player;

	if (safeIsOpen() == false)		// if the safe is closed
	{		
		vector<string> tempActions;
		if (tokens < 6 && p->getActionTokens() >= 2)	tempActions.push_back(toString(ADD_TOKEN));
		if (tokens > 0 && p->getActionTokens() >= 1)	tempActions.push_back(toString(THROW_DICE));
	}
}

void Safe::doAction(string action, void * player) {
	Player * p = (Player *)player;

	if (action == toString(ADD_TOKEN))
	{
		p->removeActionToken();
		p->removeActionToken();
		addToken();
		p->newAction(toString(ADD_TOKEN), getPos());
	}
	else if (action == toString(THROW_DICE))
	{

	}
}

bool Safe::trySafeNumber(unsigned int number) {

}
