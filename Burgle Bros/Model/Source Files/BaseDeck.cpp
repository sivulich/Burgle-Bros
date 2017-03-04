#include "../Header Files/BaseDeck.h"



BaseDeck::BaseDeck()
{
}


BaseDeck::~BaseDeck()
{
}

bool BaseDeck::discardTop()
{
	if (!isEmpty())
	{
		discarded.push_back(deck.back());
		discarded.back()->turnUp();
		deck.pop_back();
		notify();
		return true;
	}
	else return false;

}

BaseCard* BaseDeck::next()
{
	notify();
	if (discardTop() == true)
		return activeCard();
	else return NULL;
}
void BaseDeck::shuffle()
{
	random_shuffle(deck.begin(), deck.end());
	notify();
}

void BaseDeck::merge()
{
	for (auto& c : discarded)
		c->turnDown();

	deck.insert(deck.begin(), discarded.begin(), discarded.end());
	discarded.clear();
	shuffle();
	notify();
}
