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
		cout << deck.size() << endl;
		discarded.push_back(deck.back());
		deck.pop_back();
		if (discarded.back() != nullptr)
		{
			discarded.back()->turnUp();
		}
		notify();
		return true;
	}
	else return false;

}

BaseCard* BaseDeck::next()
{
	if (discardTop() == true)
	{
		notify();
		return activeCard();
	}
		
	else return nullptr;
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
