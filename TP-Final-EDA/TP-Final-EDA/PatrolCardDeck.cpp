#include "PatrolCardDeck.h"
#include "Configs.h"

PatrolCardDeck::PatrolCardDeck()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Coord c = { i,j };
			cards.push_back(PatrolCard(c));
		}
	}
	std::random_shuffle(cards.begin(), cards.end());
}


PatrolCardDeck::~PatrolCardDeck()
{
}

bool PatrolCardDeck::discardTop()
{
	if (!cards.empty())
	{
		discarded.push_front(cards.front());
		cards.pop_front();
		cards.front().turnUp();
	}
	

	return cards.empty() 
}

PatrolCard PatrolCardDeck::getTop()
{
	return cards.front();
}

PatrolCard PatrolCardDeck::getNext()
{
	if(discardTop()==true)
		return getTop();
}




void PatrolCardDeck::reset()
{
	cards.splice(cards.begin(),)
}

/*
list<PatrolCard> & PatrolCardDeck::GetCards()
{

}

list<PatrolCard> & PatrolCardDeck::GetGraveyard()
{

}*/