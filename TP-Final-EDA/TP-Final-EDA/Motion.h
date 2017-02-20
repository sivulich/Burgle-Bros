#pragma once
#include "Tile.h"
/*
You cannot enter AND leave this tile in one turn. You must stop here. If you don't  you trigger an alarm unless 
you use a hack token from the Motion Computer Room.
*/

class Motion : 	public Tile
{
public:
	Motion();
	~Motion();
};

