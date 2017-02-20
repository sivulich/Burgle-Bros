#pragma once
#include "Tile.h"

/*
Players may spend an action here to put a token on it. Each time a player encouters a Fingerprint tile,
they can spend one of these tokens to prevent an Alarm from triggering. 
*/
class ComputerRoomF :
	public Tile
{
public:
	ComputerRoomF();
	~ComputerRoomF();
};

