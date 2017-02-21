#pragma once
#include "Tile.h"

/*
Players may spend an action here to put a token on it. Each time a player encouters a Laser tile,
they can spend one of these tokens to prevent an Alarm from triggering.
*/

class ComputerRoomL :
	public Tile
{
public:
	ComputerRoomL();
	~ComputerRoomL();
};

