#include "./BaseDeck.h"

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

void BaseDeck::removeCard(string cardDesc)
{
	bool b = true;
	for (auto &it : deck)
	{
		if (it->getDescription() == cardDesc)
		{
			b = false;
			discarded.push_back(it);
			discarded.back()->turnUp();
			deck.erase(std::remove(deck.begin(), deck.end(), it), deck.end());
			notify();
			break;
		}
	}
	if (b)
		{
			discarded.push_back(new BaseCard(cardDesc,false));
			discarded.back()->turnUp();
			notify();
		}
}

BaseCard* BaseDeck::next()
{
	if (discardTop() == true)
	{
		notify();
		return activeCard();
	}
		
	else
		return nullptr;
}
void BaseDeck::shuffle()
{
	//srand((unsigned int)time(nullp));
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
