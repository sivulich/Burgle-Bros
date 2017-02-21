#pragma once
#include "Tile.h"

/*
If a player (or Guard)
 is not on this tile, it tajes 3 actions to enter. If you can't pay the extra actions, you stay in the 
 tile you came from.
 */
class Deadbolt :
	public Tile
{
public:
	Deadbolt();
	~Deadbolt();
};

