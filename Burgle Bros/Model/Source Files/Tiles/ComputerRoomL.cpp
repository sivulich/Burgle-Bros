#include "../../Header Files/Tiles/ComputerRoomL.h"


ComputerRoomL::~ComputerRoomL()
{
}

vector<string>& ComputerRoomL::getActions(Player p, Coord guardPos, Coord partnerPos) {
	Tile::getActions(p, guardPos, partnerPos);		// check if the MOVE or PEEK are possible
	if ((p.getPosition() == getPos()) && isFlipped() == true) {
		if (p.getActionTokens() > 0)				// if the player is on this tile, allow him to put a hack token
			actions.push_back(toString(ADD_TOKEN));
	}
}


void ComputerRoomL::doAction(string action, Player p, Coord guardPos, Coord partnerPos) {
	Tile::doAction(action, p);
	if (action == toString(ADD_TOKEN))
		addToken();
}
