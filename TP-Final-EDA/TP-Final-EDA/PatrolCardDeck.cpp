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



BaseCard* PatrolCardDeck::getTop()
{
	return discarded.back();
}

BaseCard* PatrolCardDeck::getNext()
{
	if(discardTop()==true)
		return getTop();
}




void PatrolCardDeck::reset()
{
	merge();
}


vector<BaseCard*> & PatrolCardDeck::GetCards()
{
	return deck;
}

vector<BaseCard*> & PatrolCardDeck::GetGraveyard()
{
	return discarded;
}