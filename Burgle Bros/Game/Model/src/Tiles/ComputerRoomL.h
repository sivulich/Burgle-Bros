#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

/*
	Players may spend an action here to put a token on it. Each time a player encouters a Laser tile,
	they can spend one of these tokens to prevent an Alarm from triggering.
*/

class ComputerRoomL : public Tile
{
public:
	ComputerRoomL(int floor, int col, int row) : Tile(COMPUTER_ROOM_L,floor, col, row) {};
	~ComputerRoomL();

	virtual vector<string> getActions(PlayerInterface * player) override;
	virtual bool doAction(string action, PlayerInterface * player) override;

	/**
	Removes 1 hack token from the tile
	*/
	void removeToken() { --hackToken; notify(); };

	void addToken() { if (hackToken < 6) ++hackToken; cout << "Current Hack tokens" << hackToken << endl; notify(); };

private:
	
};

