#pragma once

#include "Observer.h"
#include "Container.h"
#include "TileObserver.h"
#include "Floor.h"
#include "GuardDeckObserver.h"
class FloorObserver :public Observer {
public:
	FloorObserver(Floor* f,Container* p);
	void update();
private:
	GuardDeckObserver* deck;
	TileObserver* tiles[4][4];
	Container* parent;
	Container* floorGrid;
	Floor* floor;
};