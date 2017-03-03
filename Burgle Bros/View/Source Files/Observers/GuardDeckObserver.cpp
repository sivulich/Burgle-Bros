#include "../../Header Files/Observers/GuardDeckObserver.h"

GuardDeckObserver::GuardDeckObserver(Floor* f, Container* p)
{
	deck = f->getPatrolDeck();
	floor = f;
	parent = p;
	deckView = new Container(p->getHeight()/5, p->getWidth());
	deckView->setPosition(p->getHeight() *4.0/ 5, 0);
	deckView->setName(string("Deck from floor ") + to_string(floor->number()));
	zoom = new Container(p->getWidth(),p->getWidth() );
	zoom->setPosition(0, 0);
	p->addObject(deckView);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			string des = string("A") + to_string(j + 1) + string(".png");
			des[0] += i;
			cards[i][j] = new Image(string("../View/Images/Patrol/PC ") +des);
			cards[i][j]->setScale(0.9*double(zoom->getHeight()) / 4.0 / cards[i][j]->getHeight());
			cards[i][j]->setPosition(double(zoom->getHeight()) / 4.0*j, double(zoom->getHeight()) / 4.0*i);
		}
	}
	deckO = new GuardCardObserver(deckView, deck->getDeck().back());
	graveO = new GuardCardObserver(deckView, deck->getDiscarded().back());
	deckO->setPos(0, 0);
	graveO->setPos(0, deckView->getWidth()/4 );
	deck->attach(this);
}

void
GuardDeckObserver::update()
{
	if (deck->getDiscarded().empty()==true)
	{
		graveO->setOn(false);
	}
	else
	{
		graveO->setCard(deck->getDiscarded().back());
		graveO->setOn(true);
		
	}
	if (deck->getDeck().empty() == true)
	{
		deckO->setOn(false);
	}
	else
	{
		deckO->setCard(deck->getDeck().back());
		deckO->setOn(true);
		
	}
	if (graveO->isClicked() == true && parent->contains(zoom) == false)
	{
		zoom->clear();
		for (auto& card : deck->getDiscarded())
		{
			string des;
			des = card->getDescription();
			zoom->addObject(cards[des[0] - 'A'][des[1] - '1']);
		}
		parent->addObject(zoom);
	}
	else if(graveO->isClicked()==false)
	{
		parent->removeObject(zoom);
	}
	deckO->update();
	graveO->update();
}