#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

/*
Guards can see into this tile from adjacent tiles, but not through walls. You will lose a Stealth if a Guard 
is in an adjacent tile. You will lose another Stealth if the Guards enter the to your tile, as per normal.
*/
class Foyer :
	public Tile
{
public:
	Foyer(int floor, int col, int row) : Tile(FOYER,floor, col, row) {};
	~Foyer();

	/**
	Executes the tile's special actions, if any...
	@param p player who is moving
	*/
	virtual void enter(PlayerInterface * player) override;

	virtual void updateVisibleFrom(PlayerInterface * player)override;

};

