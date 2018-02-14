#pragma once
#include "Observer.h"
#include <Floor.h>
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Card.h"
#include "../Graphic Objects/Image.h"
#include <alx.hpp>
class GuardDeckObserver :public Observer
{
public:
	GuardDeckObserver(Floor* f, Container* c);
	// Shows the top card of the deck
	void showTop();
	// Hide the top card of the deck
	void hideTop();
	void update();
private:
	PatrolCardDeck* deck;
	Floor* floor;
	Container* boardCont;
	Image* cards[4][4];
	Image* back;
	Image* viewDeck;
	string lastCard;
	bool deckClicked;
	int discardedCount;
	alx::Sample* slide;
};