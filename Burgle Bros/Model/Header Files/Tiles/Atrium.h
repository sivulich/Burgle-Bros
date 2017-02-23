#pragma once
#include "Tile.h"
#include "../Player.h"

/*
You may peek up or down from this tile. Guards can see into this tile from aboveot below, making you 
lose a Stealth
*/
class Atrium : public Tile
{
public:
	Atrium(int floor, int col, int row) : Tile(floor, col, row) {};
	~Atrium();

	/**
		Adds the tile beneath and above it to the list of player visibleFrom tiles
	*/
	virtual void enterTile(void * player) override;
};

