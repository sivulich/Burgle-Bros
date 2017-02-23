#pragma once
#include "Tile.h"

/*
Guards can see into this tile from adjacent tiles, but not through walls. You will lose a Stealth if a Guard 
is in an adjacent tile. You will lose another Stealth if the Guards enter the to your tile, as per normal.
*/
class Foyer :
	public Tile
{
public:
	Foyer(int floor, int col, int row) : Tile(floor, col, row) {};
	~Foyer();

	virtual void enterTile(Player p) override;

};

