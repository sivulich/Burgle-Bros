#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
/*
If  this  tile  is  revealed  by  moving  into  it,  that player falls 1 floor. When falling, 
it does not count as entering that tile. If you are on the bottom floor, nothing happens.
Any players that enter after it is revealed do not fall, but can move downstairs for an action 
(this does count as entering).
This is one-way; you cannot move up to this tile from below.
*/

// PARA ESTA TILE, SI EL MODELO VE QUE UN PLAYER QUIERE MOVERSE A UN WALKWAY, SE FIJA SI ESTA DADO VUELTA. 
// EN ESE CASO, EL MODELO LLAMA A fallDown(). SINO LLAMA A getActions normalmente.

class Walkway :
	public Tile
{
public:
	Walkway(int floor, int col, int row) : Tile(WALKWAY,floor, col, row) { };
	~Walkway();

	/**
		Executes the tile's special actions, if any...
		@param p player who is moving
	*/
	virtual void enterTile(PlayerInterface * player) override;

	/**
		Makes the player fall to the tile beneath him, if possible
		@param p player
	*/
	bool fallDown(PlayerInterface * p);

private:
};

