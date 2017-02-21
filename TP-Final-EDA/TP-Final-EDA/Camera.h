#pragma once
#include "Tile.h"

/*
Guards on a Camera tile see all the other revealed tiles thar are cameras, on any floor.
You do not lose Stealth, but they remtely trigger an Alarm on your tile (by calling on their
radio). Note thar Guards can see through Cameras when moving though a Camera on their turn.
*/
class Camera :
	public Tile
{
public:
	Camera(int x, int y) : Tile(x, y) {};
	~Camera();

};

