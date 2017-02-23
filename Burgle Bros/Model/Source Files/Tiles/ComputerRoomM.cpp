#include "../../Header Files/Tiles/ComputerRoomM.h"


ComputerRoomM::~ComputerRoomM()
{
}

vector<string>& ComputerRoomM::getActions(Player p, Coord guardPos, Coord partnerPos) {
	Tile::getActions(p, guardPos, partnerPos);		// check if MOVE or PEEK are possible
	if ((p.getPosition() == getPos()) && p.getActionTokens() > 0)		// if the player is on this tile, allow him to put a hack token
		actions.push_back(toString(ADD_TOKEN));
}


void ComputerRoomM::doAction(string action, Player p, Coord guardPos, Coord partnerPos) {
	Tile::doAction(action, p, guardPos, partnerPos);
	if (action == toString(ADD_TOKEN))
		addToken();
}