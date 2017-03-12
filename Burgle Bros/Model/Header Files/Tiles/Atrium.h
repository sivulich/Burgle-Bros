#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
//faltaria ver casos de peek hacia arriba o abajo
/*
You may peek up or down from this tile. Guards can see into this tile from aboveot below, making you 
lose a Stealth
*/
class Atrium : public Tile
{
public:
	Atrium(int floor, int col, int row) : Tile(ATRIUM,floor, col, row){};
	~Atrium();

	/**
		Adds the tile beneath and above it to the list of player visibleFrom tiles
	*/
	void updateVisibleFrom(PlayerInterface * player)override;

	vector<Coord> whereCanIPeek()override;
};

