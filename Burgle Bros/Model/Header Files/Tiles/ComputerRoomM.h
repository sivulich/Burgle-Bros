#pragma once
#include "Tile.h"
#include "../Player.h"

/*
Players may spend an action here to put a token on it. Each time a player encouters a Motion tile,
they can spend one of these tokens to prevent an Alarm from triggering.
*/

class ComputerRoomM : public Tile
{
public:
	ComputerRoomM(int floor, int col, int row) : Tile(floor, col, row) {};
	~ComputerRoomM();


	virtual vector<string>& getActions(void * player) override;
	virtual void doAction(string action, void * player) override;

	/**
	Returns the amount of hack tokens in the tile
	*/
	unsigned int getHackTokens() { return hackToken; };
	/**
	Removes 1 hack token from the tile
	*/
	void removeToken() { --hackToken; };

private:
	void addToken() { ++hackToken; };
	unsigned int hackToken;
};

