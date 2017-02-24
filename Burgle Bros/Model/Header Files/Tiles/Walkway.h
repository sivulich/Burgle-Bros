#pragma once
#include "Tile.h"
#include "../Player.h"

class Walkway :
	public Tile
{
public:
	Walkway(int floor, int col, int row) : Tile(floor, col, row) {};
	~Walkway();

	virtual void enterTile(void * player) override;
};

