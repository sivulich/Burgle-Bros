#pragma once
#include "Tile.h"
#include "ComputerRoomM.h"
#include "../PlayerInterface.h"
/*
You cannot enter AND leave this tile in one turn. You must stop here. If you don't, you trigger an alarm unless 
you use a hack token from the Motion Computer Room.
*/

// CUANDO TERMINA EL TURNO SE LLAMA A DISARM

class Motion : 	public Tile
{
public:
	Motion(int floor, int col, int row) : Tile(MOTION, floor, col, row) { armed = false; hackerhere = false; };
	~Motion();

	/**
	Returns a vector of strings with the actions the player can do on the tile they are on
	@param p Player who wants to check the actions
	*/
	virtual vector<string> getActions(PlayerInterface * player) override;

	/**
		Applies the action given to the player
		@param action Action to execute
		@param p Player who wants to do the action
	*/
	virtual void doAction(string action, PlayerInterface * player) override;

	/**
		Executes the tile's special actions, if any...
		@param p player who is moving
	*/
	virtual void enter(PlayerInterface * player) override;

	/**
		Executes any special action when leaving the tile
	*/
	virtual void exit(PlayerInterface * player) override;


	void arm() { armed = true; };
	void disarm() { armed = false; };
	bool isArmed() { return armed; };
	void setComputerRoom(ComputerRoomM * c) { computerRoom = c; };

private:
	ComputerRoomM * computerRoom;
	bool armed;		// if true, player may not leave without triggering the alarm
	bool hackerhere; // if true there is a hacker on this tile
};

