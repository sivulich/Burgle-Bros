#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

//If a player (or Guard) is not on this tile, it takes 3 actions to enter. 
//If you can't pay the extra actions, you stay in the tile you came from.

class Deadbolt :
	public Tile
{
public:
	Deadbolt(int floor, int col, int row) : Tile(DEADBOLT,floor, col, row) { this->alarmTile = false; };
	~Deadbolt();



	//Applies the action given to the player
	//@param action Action to execute
	//@param p Player who wants to do the action
	virtual bool doAction(string action, PlayerInterface * player) override;

private:
	bool isOccupied;
};

