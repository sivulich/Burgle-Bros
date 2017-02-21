#include "Deadbolt.h"


Deadbolt::~Deadbolt()
{
}


vector<string>& Deadbolt::getActions(Player p, Coord guardPos, Coord partnerPos) {
	actions.clear();
	if (isAdjacent(p.getPosition())) {
		if (canPeek(p) == true)
			actions.push_back(toString(PEEK));

	}
}

void Deadbolt::doAction(string action, Player p);
