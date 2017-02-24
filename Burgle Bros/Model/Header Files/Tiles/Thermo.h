#pragma once
#include "Tile.h"
#include "../Player.h"

class Thermo :
	public Tile
{
public:
	Thermo(int floor, int col, int row) : Tile(floor, col, row) {};
	~Thermo();

	virtual void enterTile(void * player) override;
};

