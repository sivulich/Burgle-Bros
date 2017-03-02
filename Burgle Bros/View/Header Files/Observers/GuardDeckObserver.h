#pragma once
#include "Observer.h"
#include "../../../Model/Header Files/Floor.h"
#include "../Container.h"
#include "../Image.h"
#include "GuardCardObserver.h"
class GuardDeckObserver :public Observer {
public:
	GuardDeckObserver(Floor* f, Container* p);
	void update();
private:
	PatrolCardDeck* deck;
	Floor* floor;
	Container* parent;
	Container* zoom;
	Container* deckView;
	GuardCardObserver* deckO,*graveO;
	Image* cards[4][4];

};