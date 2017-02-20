#pragma once
#include "PatrolCard.h"
#include <list>
class PatrolCardDeck
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
	list<PatrolCard> cards;
	list<PatrolCard> discarded;
};

