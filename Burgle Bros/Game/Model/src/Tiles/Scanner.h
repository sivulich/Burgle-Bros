#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
/*

*/
class Scanner :	public Tile
{
public:
	Scanner(int floor, int col, int row) : Tile(SCANNER,floor, col, row) { this->alarmTile = true; };
	~Scanner();


	//Executes the tile's special actions, if any...
	//@param p player who is moving
	virtual void enter(PlayerInterface * player) override;

};

