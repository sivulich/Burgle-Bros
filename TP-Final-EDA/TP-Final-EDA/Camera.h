#pragma once
#include "Tile.h"
class Camera :
	public Tile
{
public:
	Camera();
	Camera(int x, int y) : Tile(x, y) {};
	~Camera();

	void peek(Player p);
	bool moveTo(Player p);

	vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);
	bool doAction(string action, Player p);
};

