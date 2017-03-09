#include "../Header Files/PatrolCardDeck.h"
#include "../Header Files/Configs.h"


bool PatrolCardDeck::createDeck(unsigned floor)
{
	deck.clear();
	discarded.clear();
	for (unsigned i = 0; i < 4; i++)
		for (unsigned j = 0; j < 4; j++)
			deck.push_back(new PatrolCard(Coord(floor,i,j)));
	this->floorNumber = floor;
	shuffle();
	for (unsigned k = 0; k < 6; k++)
		discardTop();
	return true;
}

PatrolCardDeck::~PatrolCardDeck()
{
	merge();
	for (auto &it : deck)
		delete it;
}

bool PatrolCardDeck::reset(unsigned n)
{
	if (n < (deck.size() + discarded.size()))
	{
		merge();
		for (unsigned i = 0; i < n; i++)
			discardTop();
		notify();
		return true;
	}
	return false;
}