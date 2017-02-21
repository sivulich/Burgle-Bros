#pragma once
#include "Observer.h"
#include "Floor.h"
#include "Container.h"
#include "Image.h"
class GuardDeckOberver :public Observer {
public:
	GuardDeckOberver(Floor* f, Container* p);
	void update();
private:
	PatrolCardDeck* deck;
	Floor* floor;
	Container* parent;
	Container* zoom;
	Container* deckView;
	Image* top;
	Coord topPos;
	Image* cards[4][4];
	Image* back;

};