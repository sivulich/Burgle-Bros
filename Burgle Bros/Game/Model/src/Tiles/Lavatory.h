#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
/*
This room has 3	stalls to hide in. When this tile is revelaed, place 3 Stealth tokens on it. Players may use
these tokens as Stealth while they are on this tile, instead of their own. The tokens cannot be picked up by
players.
*/

class Lavatory : public Tile
{
public:
	Lavatory(int floor, int col, int row) : Tile(LAVATORY,floor, col, row) { stealthTokens = 3; this->alarmTile = false;};
	~Lavatory();

	/**
		Returns true if you could hide from the guard. Used for Lavatory.
	*/
	bool tryToHide() override;
private:
};

