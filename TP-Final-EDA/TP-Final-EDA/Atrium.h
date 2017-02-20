#pragma once
#include "Tile.h"

class Atrium : public Tile
{
public:
	Atrium();
	Atrium(int x, int y) : Tile(x, y) {};
	~Atrium();
	
	void peek(Player p);
	bool moveTo(Player p);

	vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);
	bool doAction(string action, Player p);
};

