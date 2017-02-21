#include "GuardDeckObserver.h"

GuardDeckOberver::GuardDeckOberver(Floor* f, Container* p)
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
}
