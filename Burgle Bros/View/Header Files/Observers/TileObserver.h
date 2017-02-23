#pragma once

#include "Observer.h"
#include "Tile.h"
#include "Image.h"
#include "Container.h"
class TileObserver :public Observer {
public:
	TileObserver(Tile* t,Container* p );
	void update();
    ~TileObserver();
private:
	Image* back;
	Image* front;
	Container* parent;
	Tile* tile;
	bool set;
};
