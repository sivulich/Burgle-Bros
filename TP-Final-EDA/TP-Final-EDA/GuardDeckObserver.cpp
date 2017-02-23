#include "GuardDeckObserver.h"

GuardDeckObserver::GuardDeckObserver(Floor* f, Container* p)
{
	deck = &f->getPatrolDeck();
	floor = f;
	parent = p;
	deckView = new Container(double(p->getHeight())/3.0, double(p->getWidth()) / 3.0);
	deckView->setPosition(double(p->getHeight()) / 1.5, double(p->getWidth())*double(f->number()) / 3.0);
	zoom = new Container(double(p->getHeight()) / 1.5, double(p->getHeight()) / 1.5);
	zoom->setPosition(0, double(parent->getWidth()) / 3.0 * floor->number());
	p->addObject(deckView);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cards[i][j] = new Image(string("./Images/Patrol/PC ") + to_string(i + 'A') + to_string(j+1) + string(".jpg"));
			cards[i][j]->setPosition(double(zoom->getHeight()) / 4.0*j, double(zoom->getHeight()) / 4.0*i);
		}
	}
	deckO = new GuardCardObserver(deckView, deck->getDeck().back());
	graveO = new GuardCardObserver(deckView, deck->getDeck().back());
	graveO->setOn(false);
	deckO->setPos(0, 0);
	graveO->setPos(0, deckView->getHeight() + 10);
}

void
GuardDeckObserver::update()
{
	string des;
	if (deck->getDiscarded().empty()==true)
	{
		graveO->setOn(false);
	}
	else
	{
		graveO->setOn(true);
		graveO->setCard(deck->getDiscarded().back());
	}
	if (deck->getDeck().empty() == true)
	{
		deckO->setOn(false);
	}
	else
	{
		deckO->setOn(true);
		deckO->setCard(deck->getDeck().back());
	}
	if (graveO->isClicked() == true)
	{
		zoom->clear();
		for (auto& card : deck->getDeck())
		{
			des = card->getDescription();
			zoom->addObject(cards[des[0] - 'A'][des[1] - '1']);
		}
		parent->addObject(zoom);
	}
	else
		parent->removeObject(zoom);
	if (deckO->isClicked() == true && deck->getDeck().back()->isFlipped()==true)
	{
		zoom->clear();
		des = deck->getDeck().back()->getDescription();
		zoom->addObject(cards[des[0] - 'A'][des[1] - '1']);
		cards[des[0] - 'A'][des[1] - '1']->setBorderVisible(true);
	}
	else
	{
		parent->removeObject(zoom);
	}
}