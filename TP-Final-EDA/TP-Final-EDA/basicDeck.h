#pragma once
#include "Configs.h"

template <typename T>
class basicDeck
{
public:
	basicDeck();
	~basicDeck();
	void addCard(T & card);
	void discardTop();
	void shuffleDeck();
	vector<T>& getDeck() { return deck; };
	T peekTop();

private:
	vector<T> deck;
};

