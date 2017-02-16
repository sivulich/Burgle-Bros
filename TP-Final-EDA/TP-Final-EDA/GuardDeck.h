#pragma once
#include "Configs.h"
#include "PatrolCard.h"
class GuardDeck
{
public:
	/**

	*/
	GuardDeck();

	/**

	*/
	~GuardDeck();

	/**

	*/
	void DiscardTop();

	/**

	*/
	PatrolCard GetPatrolCard();

	/**

	*/
	PatrolCard FlipTopCard();

	/**

	*/
	void SendToBottom();

	/**

	*/
	void reset();

private:
	list<PatrolCard> cards;
	list<PatrolCard> graveyard;
};

