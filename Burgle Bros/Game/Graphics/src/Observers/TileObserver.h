#pragma once

#include "./Observer.h"

#include <Tile.h>
#include "../FlipAnimation.h"
#include "../Image.h"
#include "../Container.h"

class TileObserver :public Observer {
public:
	TileObserver(Tile* t,Container* p );
	void update();
	void setHoverable(bool b) { front->setHoverable(b); reverseTile->setHoverable(b); };
	void setClickable(bool b) { front->setClickable(b); reverseTile->setClickable(b); };
    ~TileObserver();
private:
	Container* parent;
	Tile* tile;
	vector<Image> tokens;
	Image* reverseTile;
	Image* front;
	Image* wallLeft;
	Image* wallDown;
	bool set;
};
