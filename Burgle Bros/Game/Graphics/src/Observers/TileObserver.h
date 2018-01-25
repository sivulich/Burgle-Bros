#pragma once

#include "./Observer.h"

#include <Tile.h>
#include "../Animations/FlipAnimation.h"
#include "../Graphic Objects/Card.h"
#include "../Graphic Objects/Container.h"

class TileObserver :public Observer
{
public:
	TileObserver(Tile* t, Container* floorContainer);
	void update();
	void setHoverable(bool b) { tileCard->setHoverable(b); };
	void setClickable(bool b) { tileCard->setClickable(b); };
	void enable() { tileCard->enable(); };
	void disable() { tileCard->disable(); };
	void showSafeNumber();
	double size();
	double xpos();
	double ypos();
	pair<int, int> pos() { return tileCard->getPos(); };

	~TileObserver();
private:
	// Pointer to the container in which the tile is
	Container* floorContainer;
	// Pointer to observed tile
	Tile* tile;

	//Graphics object
	Image *safeNumber;
	Image *alarmToken;
	Image *crackToken;
	Image *crowToken;
	Image *stairToken;
	Image *openToken;
	vector<Image *> hackTokens;

	Card * tileCard;
	bool flipped;
	bool cracked;
};
