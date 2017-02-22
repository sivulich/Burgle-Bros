#include "PatrolCardDeck.h"
#include "Configs.h"

PatrolCardDeck::PatrolCardDeck()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Coord c = { 0,i,j };
			deck.push_back(new PatrolCard(c));
		}
	}
	shuffle();
}


PatrolCardDeck::~PatrolCardDeck()
{
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


/*
vector<BaseCard*> & PatrolCardDeck::GetCards()
{
	return deck;
}

vector<BaseCard*> & PatrolCardDeck::GetGraveyard()
{
	return discarded;
}*/