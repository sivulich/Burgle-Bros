#pragma once

#include "Observer.h"
#include "../Graphic Objects/Container.h"
#include "./TileObserver.h"
#include <Floor.h>
#include "./GuardDeckObserver.h"
#include "./GuardObserver.h"
class FloorObserver :public Observer
{
public:
	// Recives a floor pointer and the container for the tiles
	FloorObserver(Floor* f,Container* floorContainer);
	void update();
	Container* getFloorGrid() { return secondGrid; };
	TileObserver** operator[](size_t i) { return tiles[i]; };
private:
	GuardDeckObserver * deck;
	GuardObserver * guard;
	TileObserver * tiles[4][4];

	Container* parent;
	Container* floorGrid;
	Container* secondGrid;
	Floor* floor;
};