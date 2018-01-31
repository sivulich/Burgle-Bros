#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
//falta hacer

/*
Guards on a Camera tile see all the other revealed tiles that are cameras, on any floor.
You do not lose Stealth, but they remotely trigger an Alarm on your tile (by calling on their
radio). Note that Guards can see through Cameras when moving through a Camera Tile on their turn.
*/
class Camera :
	public Tile
{
public:
	Camera(int floor, int col, int row) : Tile(CAMERA, floor, col, row) { this->alarmTile = false; };
	~Camera();

	void addCamera(Tile * cam) { otherCameras.push_back(cam); };
private:
	vector<Tile *> otherCameras;
};

