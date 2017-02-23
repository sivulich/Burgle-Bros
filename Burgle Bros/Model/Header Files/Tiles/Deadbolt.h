#pragma once
#include "Tile.h"

/*
	If a player (or Guard) is not on this tile, it takes 3 actions to enter. 
	If you can't pay the extra actions, you stay in the tile you came from.
 */
class Deadbolt :
	public Tile
{
public:
	Deadbolt(int floor, int col, int row) : Tile(floor, col, row) {};
	~Deadbolt();

	virtual vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);
	virtual void doAction(string action, Player p, Coord guardPos, Coord partnerPos);

};

