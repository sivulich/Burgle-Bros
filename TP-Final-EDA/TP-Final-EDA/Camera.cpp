#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

vector<string>& Camera::getActions(Player p, Coord guardPos, Coord partnerPos) {
	actions.clear();
	if (isAdjacent(p.getPosition()))	//if the player is adjacent to the tile, get the list of actions
	{
		if (p.getActionTokens > 0 && isFlipped() == true)
			actions.push_back("PEEK");
		if (p.getActionTokens > 0)
			actions.push_back("MOVE");
	}
	return actions;
}

bool Camera::doAction(string action, Player p)
{
	if (action == "PEEK")
		peek(p);
	else if (action == "MOVE")
		move(p);
}

void Camera::peek(Player p) {
	p.removeActionToken();
	turnUp();
	addPlayerAction(p, "PEEK");
}

bool Camera::moveTo(Player p) {
	p.removeActionToken();
	p.move(getCoord());
	addPlayerAction(p, "MOVE");
}