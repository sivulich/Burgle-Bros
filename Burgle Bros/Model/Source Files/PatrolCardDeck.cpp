#include "../Header Files/PatrolCardDeck.h"
#include "../Header Files/Configs.h"


bool PatrolCardDeck::createDeck(unsigned floor)
{
	for (unsigned i = 0; i < 4; i++)
	{
		for (unsigned j = 0; j < 4; j++)
		{
			Coord c = { floor,i,j };
			deck.push_back(new PatrolCard(c));
		}
	}
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
		return true;
	}
	return false;
}