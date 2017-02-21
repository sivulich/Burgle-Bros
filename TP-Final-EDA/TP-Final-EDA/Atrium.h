#pragma once
#include "Tile.h"
/*
You may peek up or down from this tile. Guards can see into this tile from aboveot below, making you 
lose a Stealth
*/
class Atrium : public Tile
{
public:
	Atrium(int x, int y) : Tile(x, y) {};
	~Atrium();

	/**
		Moves the player to the atrium tile and adds the tile beneath and above it to the list of player visibleFrom tiles
	*/
	virtual void moveTo(Player p) override;	
};

