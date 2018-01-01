#pragma once
#include "Observer.h"
#include <Floor.h>
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Card.h"
#include "../Graphic Objects/Image.h"

class GuardDeckObserver :public Observer
{
public:
	GuardDeckObserver(Floor* f, Container* c);
	void update();
private:
	PatrolCardDeck* deck;
	Floor* floor;
	Container* boardCont;
	Image* cards[4][4];
	Image* back;
	string lastCard;
	bool deckClicked;
	int discardedCount;
};