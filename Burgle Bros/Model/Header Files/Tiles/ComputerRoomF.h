#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

/*
Players may spend an action here to put a token on it. Each time a player encouters a Fingerprint tile,
they can spend one of these tokens to prevent an Alarm from triggering. 
*/
class ComputerRoomF :
	public Tile
{
public:
	ComputerRoomF(int floor, int col, int row) : Tile(COMPUTER_ROOM_F,floor, col, row) {};
	~ComputerRoomF();

	virtual vector<string> getActions(PlayerInterface * player) override;
	virtual void doAction(string action, PlayerInterface * player) override;

	/**
		Returns the amount of hack tokens in the tile
	*/
	int getHackTokens(){ return hackToken; };
	/**
		Removes 1 hack token from the tile
	*/
	void removeToken() { --hackToken; };

private:
	void addToken() { ++hackToken; };
	int hackToken;
};

