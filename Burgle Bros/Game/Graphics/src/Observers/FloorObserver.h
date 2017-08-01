#pragma once

#include "Observer.h"
#include "../Container.h"
#include "./TileObserver.h"
#include <Floor.h>
#include "./GuardDeckObserver.h"
#include "./GuardObserver.h"
class FloorObserver :public Observer {
public:
	FloorObserver(Floor* f,Container* p);
	void update();
	Container* getFloorGrid() { return secondGrid; };
	TileObserver** operator[](size_t i) { return tiles[i]; };
private:
	GuardDeckObserver* deck;
	GuardObserver* guard;
	TileObserver* tiles[4][4];
	Container* parent;
	Container* floorGrid;
	Container* secondGrid;
	Floor* floor;
};