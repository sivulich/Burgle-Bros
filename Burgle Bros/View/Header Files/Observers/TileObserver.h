#pragma once

#include "Observer.h"
#include "../Model/Header Files/Tiles/Tile.h"
#include "../Image.h"
#include "../Container.h"
class TileObserver :public Observer {
public:
	TileObserver(Tile* t,Container* p );
	void update();
    ~TileObserver();
private:

	Container* parent;
	Tile* tile;
	vector<Image> tokens;
	Image* reverseTile;
	Image* front;
	bool set;
};
