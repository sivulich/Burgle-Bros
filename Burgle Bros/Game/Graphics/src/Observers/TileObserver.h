#pragma once

#include "./Observer.h"

#include <Tile.h>
#include "../Animations/FlipAnimation.h"
#include "../Graphic Objects/Image.h"
#include "../Graphic Objects/Container.h"


class TileObserver :public Observer
{
public:
	TileObserver(Tile* t,Container* p );
	void update();
	void setHoverable(bool b) { front->setHoverable(b); reverseTile->setHoverable(b); };
	void setClickable(bool b) { front->setClickable(b); reverseTile->setClickable(b); };
    ~TileObserver();
private:
	// Pointer to the container in which the tile is
	Container* parent;
	// Pointer to observed tile
	Tile* tile;
	vector<Image> tokens;

	Image* reverseTile;
	Image* front;

	Image* wallLeft;
	Image* wallDown;
	bool set;
};
