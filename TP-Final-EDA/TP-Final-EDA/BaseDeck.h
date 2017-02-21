#pragma once
#include "BaseCard.h"
#include "Configs.h"

class BaseDeck
{
public:
	BaseDeck();
	~BaseDeck();
	bool isEmpty() { return deck.empty(); };
	void discardTop();
	BaseCard* next();
	void merge();
	void shuffle();
	BaseCard* top();
	vector<BaseCard*> getDiscarded();

protected:
	vector<BaseCard*> deck;
	vector<BaseCard*> discarded;
};

