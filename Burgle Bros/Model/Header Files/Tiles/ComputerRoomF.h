#pragma once
#include "Tile.h"

/*
Players may spend an action here to put a token on it. Each time a player encouters a Fingerprint tile,
they can spend one of these tokens to prevent an Alarm from triggering. 
*/
class ComputerRoomF :
	public Tile
{
public:
	ComputerRoomF(int floor, int col, int row) : Tile(floor, col, row) {};
	~ComputerRoomF();


	virtual vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);
	virtual void doAction(string action, Player p, Coord guardPos, Coord partnerPos);
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

