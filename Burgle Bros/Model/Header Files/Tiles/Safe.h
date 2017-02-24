#pragma once
#include "Tile.h"
#include "../Player.h"
/*
Safes are the goal. Roll the combination to open them. When opened, draw a Loot, and increase the Guard's 
movement die by one on this floor and all those below it.
*/

class Safe : public Tile
{
public:
	Safe(int floor, int col, int row) : Tile(floor, col, row) {};
	~Safe();

	/**
	Returns a vector of strings with the actions the player can do on the tile they are on
	@param p Player who wants to check the actions
	*/
	virtual vector<string>& getActions(void * player) override;

	/**
	Applies the action given to the player
	@param action Action to execute
	@param p Player who wants to do the action
	*/
	virtual void doAction(string action, void * player) override;

	/**
	Executes the tile's special actions, if any...
	@param p player who is moving
	*/
	virtual void enterTile(void * player) override;
};

