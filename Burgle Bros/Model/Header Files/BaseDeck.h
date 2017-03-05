#pragma once
#include "BaseCard.h"
#include "Configs.h"
#include "BaseModel.h"
//Top of deck is represented by vector´s back
//Top of discarded deck is considered to be active card
class BaseDeck:public BaseModel
{
public:
	BaseDeck();
	~BaseDeck();

	/**
	@return boolean value, true if deck is empty, otherwise it is false.
	*/
	bool isEmpty() { return deck.empty(); };

	/**
	removes top card from deck and moves it to the top of discarded deck.
	@return boolean value, true if card could be discarded, false if deck was empty
	*/
	bool discardTop();

	/**
		Removes top card of deck from main deck and moves it to the bottom of it
	*/
	void topToBottom() { deck.insert(deck.begin(), topCard()); deck.pop_back(); notify(); };

	/**
	discards deck´s top card and returns cards value
	@return BaseCard *, if deck is empty value is NULL
	*/
	BaseCard* next();

	/**
	randomly changes position of all cards in main deck
	*/
	void shuffle();

	/**
	removes cards from discarded deck, turns them down and adds them to main deck. main deck is then shuffled
	*/
	void merge();

	/**
	@return top of discarded deck (BaseCard*)
	*/
	BaseCard* activeCard() { return discarded.back(); };

	/**
	@return top of main deck (BaseCard*)
	*/
	BaseCard* topCard() { return deck.back(); };

	/**
	@returns main deck (vector<BaseCard*>)
	*/
	vector<BaseCard*> getDeck() { return deck; };

	/**
	@returns discarded deck (vector<BaseCard*>)
	*/
	vector<BaseCard*> getDiscarded() { return discarded; };

protected:
	vector<BaseCard*> deck;
	vector<BaseCard*> discarded;
};

