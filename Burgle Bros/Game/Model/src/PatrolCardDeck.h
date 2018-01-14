#pragma once
#include "./PatrolCard.h"
#include "./BaseDeck.h"
#include <list>

class PatrolCardDeck : public BaseDeck
{
public:
	/**
		Construct a patrol card deck with its floor number
	*/
	PatrolCardDeck(unsigned n) : floorNumber(n)
	{
		beingSpied = false;
		createDeck();
		spiedCard = nullptr;
	};


	/**

	*/
	~PatrolCardDeck();

	/**
		Create all patrol cards, shuffle and delete 6 of them
	*/
	void createDeck();
	
	/**
		Function merges cards in discarded deck with main deck (discarded cards are turned down). Main deck is shuffled 
	*/
	void reset();

	/**
	
	*/
	void spyTop() { spiedCard = (PatrolCard *)topCard(); beingSpied = true; notify(); };

	/**
		Returns the floor of the patrol card deck
	*/

	void noLongerSpied() { spiedCard = nullptr; beingSpied = false; notify(); };
	unsigned floor() { return floorNumber; };

private:
	unsigned floorNumber;
	PatrolCard * spiedCard;
	bool beingSpied;
};

