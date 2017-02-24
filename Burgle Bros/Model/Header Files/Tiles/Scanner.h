#pragma once
#include "Tile.h"
#include "../Player.h"
/*

*/
class Scanner :	public Tile
{
public:
	Scanner(int floor, int col, int row) : Tile(floor, col, row) {};
	~Scanner();


	/**
	Executes the tile's special actions, if any...
	@param p player who is moving
	*/
	virtual void enterTile(void * player) override;

};

