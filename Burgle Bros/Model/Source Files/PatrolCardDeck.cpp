#include "PatrolCardDeck.h"
#include "Configs.h"

PatrolCardDeck::PatrolCardDeck(unsigned discarded)
{
	for (unsigned i = 0; i < 4; i++)
	{
		for (unsigned j = 0; j < 4; j++)
		{
			Coord c = { 0,i,j };
			deck.push_back(new PatrolCard(c));
		}
	}
	shuffle();
	if (discarded < 16)
	{
		for (unsigned k = 0; k < discarded; k++)
			discardTop();
	}
}


PatrolCardDeck::~PatrolCardDeck()
{
	merge();
	for (auto &it : deck)
	{
		delete it;
	}
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