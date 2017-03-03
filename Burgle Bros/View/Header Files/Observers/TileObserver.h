#pragma once

#include "Observer.h"
#include "../Model/Header Files/Tiles/Tile.h"
#include "../Image.h"
#include "../Container.h"

class TileObserver :public Observer {
public:
	TileObserver(Tile* t,Container* p );
	void update();
	void setGuard();
	void setPlayer(int pNum);
	void setAlarm();
    ~TileObserver();
private:

	Container* parent;
	Container* toDraw;
	Tile* tile;
	bool set;
};
