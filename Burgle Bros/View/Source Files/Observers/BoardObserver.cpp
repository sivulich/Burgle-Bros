#include "../../Header Files/Observers/BoardObserver.h"

BoardObserver::BoardObserver(Board* b, Container* c)
{
	parent = c;
	board = b;
	for (int i=0;i<3;i++)
	{
		toDraw[i]= new Container(c->getHeight()*2.0 / 3.0, c->getHeight() * 2.0 / 3.0 * 4.0 / 5.0);
		toDraw[i]->setPosition(c->getHeight() / 16, c->getWidth() / 50 + i*c->getWidth() / 3);
	}
	for (int i = 0; i < 3; i++)
	{
		floors[i] = new FloorObserver(&(*b)[i], toDraw[i]);
	}
	for (auto & fl : toDraw)
		parent->addObject(fl);
	board->attach(this);
}

void
BoardObserver::update()
{
	for (auto & f : floors)
		f->update();
}