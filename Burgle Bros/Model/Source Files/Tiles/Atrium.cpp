#include "../../Header Files/Tiles/Atrium.h"


void Atrium::updateVisibleFrom(PlayerInterface * player) 
{
	player->clearVisibleFrom();
	player->addVisibleTile(getPos());

	if (floor() > 0)
		player->addVisibleTile(Coord(floor() - 1, col(), row()));
	if (floor() < 2)
		player->addVisibleTile(Coord(floor() + 1, col(), row()));
}

vector<Coord> Atrium::whereCanIPeek()
{
	vector<Coord> v = adjacent;
	
	if (floor() > 0)
		v.push_back(Coord(floor() - 1, col(), row()));
	if (floor() < 2)
		v.push_back(Coord(floor() + 1, col(), row()));
	return v;
}