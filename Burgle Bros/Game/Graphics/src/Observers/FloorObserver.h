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
	// Recives a floor pointer and the container of the board
	FloorObserver(Floor* f, Container* boardContainer);
	bool guardIsMoving() { return guard->guardIsMoving(); };
	virtual void update();
	Container * getContainer() { return floorContainer; }
	TileObserver** operator[](size_t i) { return tiles[i]; };
private:
	Floor* floor;
	TileObserver * tiles[4][4];
	Tile* safe;
	bool safeIsFlipped;
	Image * numbers[8];
	Container* floorContainer;
	Container* boardContainer;
	GuardDeckObserver * deck;
	GuardObserver * guard;
};