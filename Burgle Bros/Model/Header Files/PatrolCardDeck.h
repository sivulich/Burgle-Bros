#pragma once
#include "PatrolCard.h"
#include "BaseDeck.h"
#include <list>

class PatrolCardDeck : public BaseDeck
{
public:
	/**
	*/
	PatrolCardDeck() {};


	/**

	*/
	~PatrolCardDeck();

	/**
	
	*/
	bool createDeck(unsigned floor);
	
	/**
	function merges cards in discarded deck with main deck (discarded cards are turned down). Main deck is shuffled 
	n amount of cards are discarded automatically to the discarded deck
	@addparams n amount of cards to be discarded from deck 
	@return if deck could be correctly reseted true is returned, else false. (problems could occur if n is a number higher than the total amount of cards found in both decks)
	*/
	bool reset(unsigned n);

	/**
	Returns the floor of the patrol card deck
	*/
	unsigned floor() { return floorNumber; };

private:
	unsigned floorNumber;
};

