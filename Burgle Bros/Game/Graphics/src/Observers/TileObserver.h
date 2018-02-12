#pragma once

#include "./Observer.h"

#include <Tile.h>
#include "../Animations/FlipAnimation.h"
#include "../Graphic Objects/Card.h"
#include "../Graphic Objects/Container.h"

class TileObserver :public Observer
{
public:
	TileObserver(Tile* t, Container* floorContainer, Container* boardContainer);
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
	void zoom();
	void unZoom();
	~TileObserver();
private:
	// Pointer to the container in which the tile is
	Container* floorContainer;
	Container* boardContainer;
	// Pointer to observed tile
	Tile* tile;

	//Graphics object
	Image *safeNumber;
	Image *alarmToken;
	Image *crackToken;
	Image *crowToken;
	Image *stairToken;
	Image *openToken;
	Image *persianKitty;
	Image *goldBar;
	vector<Image *> hackTokens;
	vector<Image *> stealthTokens;

	Card * tileCard;
	Image * zoomedCard;
	bool flipped;
	bool cracked;
	bool hasGoldBar;
	bool hasKitty;
};
