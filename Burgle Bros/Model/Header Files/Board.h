#pragma once
#include "../Header Files/Configs.h"
#include "../Header Files/Floor.h"
#include "../Header Files/Player.h"
#include "../Header Files/Loots/Loot.h"
#include "../Header Files/Tiles/Tile.h"

class Board
{
public:
	Board();
	~Board();

	/**
		Returns the floor i
	*/
	Floor* operator[](size_t i) { return (floor[i]); };

private:
	Floor* floor[3];
	vector<Coord> adjacent[3][4][4];

	Loot loots[3];

};



