#include "basicDeck.h"


template <typename T>
basicDeck<T>::basicDeck()
{
	
}

template <typename T>
basicDeck<T>::~basicDeck()
{
}

/**
	Adds the card to the top of the deck
*/
template <typename T>
void basicDeck<T>::addCard(T & card) {
	deck.push_back(card);
}
/**
	Deletes the card at the top of the deck
*/
template <typename T>
void basicDeck<T>::discardTop() {
	deck.pop_back();
}
/**
	Shuffles the deck
*/
template <typename T>
void basicDeck<T>::shuffleDeck() {
	random_shuffle(deck.begin(), deck.end());
}
/**
	Returns a copy of the top card
*/
template <typename T>
T basicDeck<T>::peekTop() {
	return *deck.end();
}