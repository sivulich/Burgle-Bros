#pragma once
#include "Observer.h"
#include "Floor.h"
#include "Container.h"
#include "Image.h"
class GuardDeckObserver :public Observer {
public:
	GuardDeckObserver(Floor* f, Container* p);
	void update();
private:
	PatrolCardDeck* deck;
	bool empty;
	Floor* floor;
	Container* parent;
	Container* zoom;
	Container* deckView;
	Image* top;
	Coord topPos;
	Image* cards[4][4];
	Image* back;

};