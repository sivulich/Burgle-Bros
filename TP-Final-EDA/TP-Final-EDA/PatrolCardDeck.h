#pragma once
#include "PatrolCard.h"
#include "BaseDeck.h"
#include <list>

class PatrolCardDeck : public BaseDeck
{
public:
	/**

	*/
	PatrolCardDeck();

	/**

	*/
	~PatrolCardDeck();

	/**

	*/
	bool discardTop();

	/**

	*/
	PatrolCard getTop();

	/**

	*/
	PatrolCard getNext();


	/**

	*/
	void reset();

	/**

	*/
	list<PatrolCard> & GetCards();

	/**

	*/
	list<PatrolCard> & GetGraveyard();

private:
	
};

