#pragma once
#include "Tile.h"

/*
It takes two actions to enter this tile. If you can't or you don't want to spend the extra action, an Alarm 
goes off unless you us a Hack token from the Laser Computer Room
*/

class Laser :
	public Tile
{
public:
	Laser();
	~Laser();
};

