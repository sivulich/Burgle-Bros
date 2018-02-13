#include "./PatrolCardDeck.h"
#include "./Configs.h"


void PatrolCardDeck::createDeck()
{
	for (auto& it : deck)
		if(it!=nullptr)
			delete it;

	for (auto& it : discarded)
		if (it != nullptr)
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
	notify();
}

PatrolCardDeck::~PatrolCardDeck()
{
	merge();
	for (auto &it : deck)
		if(it!=nullptr)
			delete it;
}

void PatrolCardDeck::reset()
{
	createDeck();

	notify();
}

void PatrolCardDeck::removeCard(string cardDesc)
{
	bool b = true;
	vector<BaseCard *>::iterator it = deck.begin();
	for (it;it!=deck.end();it++)
	{
		if ((*it)->getDescription() == cardDesc)
		{
			b = false;
			discarded.push_back(*it);
			discarded.back()->turnUp();
			deck.erase(it);
			notify();
			break;
		}
	}
	if (b)
	{
		discarded.push_back(new PatrolCard(cardDesc));
		discarded.back()->turnUp();
		notify();
	}
}


void PatrolCardDeck::moveCardtoTop(Coord pos)
{
	bool b = true;
	vector<BaseCard *>::iterator it = deck.begin();
	for (it; it != deck.end(); it++)
	{
		if (((PatrolCard *)*it)->getCoord() == pos)
		{
			b = false;
			deck.push_back(new PatrolCard(pos));
			deck.erase(it);
			break;
		}
	}
	if(b)
	{ 
		deck.erase(deck.begin());
		deck.push_back(new PatrolCard(pos));
	}
}