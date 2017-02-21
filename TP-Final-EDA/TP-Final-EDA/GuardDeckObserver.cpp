#include "GuardDeckObserver.h"

GuardDeckObserver::GuardDeckObserver(Floor* f, Container* p)
{
	
	back = new Image(string("./Images/Patrol/PC R.jpg"));
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
			cards[i][j] = new Image(string("./Images/Patrol/PC ") + to_string(i + 'A') + to_string(j) + string(".jpg"));
			cards[i][j]->setPosition(double(zoom->getHeight()) / 4.0*j, double(zoom->getHeight()) / 4.0*i);
		}
	}
	topPos.col = -1;
	topPos.row = -1;
	topPos.floor = 0;
	top = nullptr;
	back->setPosition(0, 0);
	back->setScale(double(deckView->getHeight()) / double(back->getHeight()));
	deckView->addObject(back);
	empty = false;
}

void
GuardDeckObserver::update()
{
	string des;
	if (deck->GetGraveyard().empty()==true)
	{
		if (top != nullptr)
		{
			deckView->removeObject(top);
			delete top;
		}
	}
	else
	{
		des = deck->GetGraveyard().back()->getDescription();
		if (des[0] - 'A' != topPos.col || des[1] - '0' != topPos.row)
		{
			topPos.col = des[0] - 'A';
			topPos.row = des[1] - '0';
			if (top != nullptr)
			{
				deckView->removeObject(top);
				delete top;
			}
			top = new Image(string("./Images/Patrol/PC ") + des + string(".jpg"));
			top->setScale(double(deckView->getHeight()) / double(top->getHeight()));
			top->setPosition(0, top->getWidth() + 10);
		}
	}
	if (deck->GetCards().empty() == true)
	{
		deckView->removeObject(back);
		empty = true;
	}
	else
	{
		if (empty == true)
			deckView->addObject(back);
		empty = false;
	}
	if (top->isClicked() == true)
	{
		zoom->clear();
		for (auto& card : deck->GetGraveyard())
		{
			des = card->getDescription();
			zoom->addObject(cards[des[0] - 'A'][des[1] - '0']);
		}
		parent->addObject(zoom);
	}
	else
		parent->removeObject(zoom);
}