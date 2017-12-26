#pragma once
#include "Observer.h"
#include <Floor.h>
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Image.h"
#include "./GuardCardObserver.h"
class GuardDeckObserver :public Observer
{
public:
	GuardDeckObserver(Floor* f, Container* c, double tileSize, pair<int, int> p[4][4]);
	void update();
private:
	PatrolCardDeck* deck;
	Floor* floor;
	Container* parent;
	Container* zoom;
	Container* deckView;
	GuardCardObserver* deckO,*graveO;
	Image* cards[4][4];
	bool startedRetraction;
};