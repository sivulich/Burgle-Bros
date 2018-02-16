#pragma once

#include "Observer.h"
#include "../Graphic Objects/Container.h"
#include <Floor.h>
#include "./GuardDeckObserver.h"
#include "./GuardObserver.h"
#include "./TileObserver.h"

class FloorObserver :public Observer
{
public:
	// Recives a floor pointer and the container of the board
	FloorObserver(Floor* f, Container* boardContainer);
	~FloorObserver();
	bool guardIsMoving() { return guard->guardIsMoving(); };
	virtual void update();
	Container * getContainer() { return floorContainer; }
	TileObserver** operator[](size_t i) { return tiles[i]; };
	void showTopPatrol() { deck->showTop(); };
	void hideTopPatrol() { deck->hideTop(); };
	// Zoom the selected tile
	void zoomTile(Coord c);
	// Unzoom the tile
	void unZoomTile();

private:
	Floor* floor;
	TileObserver * tiles[4][4];
	Coord * zoomedTile;
	Tile* safe;
	bool safeIsFlipped;
	Image * numbers[8];
	Container* floorContainer;
	Container* boardContainer;
	GuardDeckObserver * deck;
	GuardObserver * guard;
};