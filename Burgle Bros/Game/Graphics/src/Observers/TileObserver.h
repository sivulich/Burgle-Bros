#pragma once

#include "./Observer.h"

#include <Tile.h>
#include "../Animations/FlipAnimation.h"
#include "../Graphic Objects/Card.h"
#include "../Graphic Objects/Container.h"


class TileObserver :public Observer
{
public:
	TileObserver(Tile* t,Container* floorContainer );
	void update();
	void setHoverable(bool b) { tileCard->setHoverable(b); };
	void setClickable(bool b) { tileCard->setClickable(b); };
    ~TileObserver();
private:
	// Pointer to the container in which the tile is
	Container* floorContainer;
	// Pointer to observed tile
	Tile* tile;
	vector<Image> tokens;
	Card * tileCard;
	bool flipped;
};
