#include "GuardDeckObserver.h"

GuardDeckObserver::GuardDeckObserver(Floor* f, Container* p)
{
	deck = &f->getPatrolDeck();
	floor = f;
	parent = p;
	deckView = new Container(double(p->getHeight())/3.0, double(p->getWidth()) / 3.0);
	deckView->setPosition(double(p->getHeight()) / 1.5, double(p->getWidth())*double(f->getNumber()) / 3.0);
	zoom = new Container(double(p->getHeight()) / 1.5, double(p->getHeight()) / 1.5);
	zoom->setPosition(0, double(parent->getWidth()) / 3.0 * floor->getNumber());
	p->addObject(deckView);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cards[i][j] = new Image(string("./Images/Patrol/PC ") + to_string(i + 'A') + to_string(j+1) + string(".jpg"));
			cards[i][j]->setPosition(double(zoom->getHeight()) / 4.0*j, double(zoom->getHeight()) / 4.0*i);
		}
	}
	deckO = new GuardCardObserver(deckView, deck->GetCards().back());
	graveO = new GuardCardObserver(deckView, deck->GetCards().back());
	graveO->setOn(false);
	deckO->setPos(0, 0);
	graveO->setPos(0, deckView->getHeight() + 10);
}

void
GuardDeckObserver::update()
{
	string des;
	if (deck->GetGraveyard().empty()==true)
	{
		graveO->setOn(false);
	}
	else
	{
		graveO->setOn(true);
		graveO->setCard(deck->GetGraveyard().back());
	}
	if (deck->GetCards().empty() == true)
	{
		deckO->setOn(false);
	}
	else
	{
		deckO->setOn(true);
		deckO->setCard(deck->GetCards().back());
	}
	if (graveO->isClicked() == true)
	{
		zoom->clear();
		for (auto& card : deck->GetGraveyard())
		{
			des = card->getDescription();
			zoom->addObject(cards[des[0] - 'A'][des[1] - '1']);
		}
		parent->addObject(zoom);
	}
	else
		parent->removeObject(zoom);
	if (deckO->isClicked() == true && deck->GetCards().back()->isFlipped()==true)
	{
		zoom->clear();
		des = deck->GetCards().back()->getDescription();
		zoom->addObject(cards[des[0] - 'A'][des[1] - '1']);
		cards[des[0] - 'A'][des[1] - '1']->setBorderVisible(true);
	}
	else
	{
		parent->removeObject(zoom);
	}
}