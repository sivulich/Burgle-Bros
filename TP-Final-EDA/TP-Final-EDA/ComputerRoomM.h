#pragma once
#include "Tile.h"

/*
Players may spend an action here to put a token on it. Each time a player encouters a Motion tile,
they can spend one of these tokens to prevent an Alarm from triggering.
*/

class ComputerRoomM : public Tile
{
public:
	ComputerRoomM(int x, int y) : Tile(x, y) {};
	~ComputerRoomM();


	virtual vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);
	virtual void doAction(string action, Player p);

	void removeToken() { hackToken = false; };

private:
	void addToken() { hackToken = true; };
	bool hackToken;
};

