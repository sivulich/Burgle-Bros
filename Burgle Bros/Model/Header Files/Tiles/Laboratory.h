#pragma once
#include "Tile.h"

/*
	First player to enter this tile draws a tool card.
	For our version of Burgle Bros, this tile does nothing.
*/
class Laboratory :
	public Tile
{
public:
	Laboratory(int floor, int col, int row) : Tile(floor, col, row) {};
	~Laboratory();
};

