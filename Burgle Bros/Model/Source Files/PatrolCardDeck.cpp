#include "../Header Files/PatrolCardDeck.h"
#include "../Header Files/Configs.h"


void PatrolCardDeck::createDeck()
{
	for (auto& it : deck)
		delete it;

	for (auto& it : discarded)
		delete it;

	deck.clear();
	discarded.clear();
	for (unsigned i = 0; i < 4; i++)
		for (unsigned j = 0; j < 4; j++)
			deck.push_back(new PatrolCard(Coord(floorNumber,i,j)));
	shuffle();

	// Discard 6 cards 
	for (unsigned k = 0; k < 6; k++)
	{
		delete deck.back();
		deck.pop_back();
	}
	
}

PatrolCardDeck::~PatrolCardDeck()
{
	merge();
	for (auto &it : deck)
		delete it;
}

void PatrolCardDeck::reset()
{
	createDeck();

	notify();
}