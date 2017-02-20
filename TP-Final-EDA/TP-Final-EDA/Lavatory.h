#pragma once
#include "Tile.h"

/*
This room has 3stalls to hide in. When this tile is revelaed, place 3 Stealth tokens on it. Players may use
these tokens as Stealth while they are on this tile, instead of their own. The tokens cannot be picked up by
players.
*/

class Lavatory : public Tile
{
public:
	Lavatory();
	~Lavatory();
};

