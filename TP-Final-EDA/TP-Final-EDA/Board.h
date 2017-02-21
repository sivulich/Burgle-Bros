#pragma once
#include "Configs.h"
#include "Floor.h"
#include "Player.h"
#include "Loot.h"
#include "Tile.h"

class Board
{
public:
	Board();
	~Board();

	/**
		Returns the floor i
	*/
	Floor& operator[](size_t i) { return *(floor[i]); };

private:

	Floor* floor[3];
	vector<Coord> adjacent[3][4][4];

	Loot loots[3];

};



