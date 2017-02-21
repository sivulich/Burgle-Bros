#include "BaseDeck.h"



BaseDeck::BaseDeck()
{
}


BaseDeck::~BaseDeck()
{
}

void BaseDeck::discardTop()
{
	discarded.push_back(deck.back());
	discarded.back()->turnUp();
	deck.pop_back();
	
}

BaseCard* BaseDeck::next()
{
	discardTop();
	return top();
}
void BaseDeck::shuffle()
{
	random_shuffle(deck.begin(), deck.end());
}

void BaseDeck::merge()
{
	for (auto& c : discarded)
		c->turnDown();

	deck.insert(deck.begin(), discarded.begin(), discarded.end());
	discarded.clear();
	shuffle();
}

BaseCard* BaseDeck::top()
{
	return discarded.back();
}
vector<BaseCard*> BaseDeck::getDiscarded()
{
	return discarded;
}
