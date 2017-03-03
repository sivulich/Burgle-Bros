#pragma once

#include "Observer.h"
#include "../Container.h"
#include "TileObserver.h"
#include "../../../Model/Header Files/Floor.h"
#include "GuardDeckObserver.h"
class FloorObserver :public Observer {
public:
	FloorObserver(Floor* f,Container* p);
	void update();
	Container* getFloorGrid() { return floorGrid; };
private:
	GuardDeckObserver* deck;
	TileObserver* tiles[4][4];
	Container* parent;
	Container* floorGrid;
	Floor* floor;
};