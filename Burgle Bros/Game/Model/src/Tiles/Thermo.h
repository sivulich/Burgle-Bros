#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

//If you end your actions on a Thermo tile an alarm will go off. If you are moved here during other turns,
//it does not trigger.

class Thermo :
	public Tile
{
public:
	Thermo(int floor, int col, int row) : Tile(THERMO,floor, col, row) { this->alarmTile = true; };
	~Thermo();

//Executes the tile's special actions, if any...
//@param p player who is moving
	virtual void enter(PlayerInterface * player) override;
};

