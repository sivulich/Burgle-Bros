#include "../../Header Files/Observers/BoardObserver.h"

BoardObserver::BoardObserver(Board* b, Container* c)
{
	parent = c;
	board = b;
	toDraw = new Container(parent->getHeight() * 2.0 / 3.0, parent->getHeight() * 2.0 *13.0 / 16.0);
	toDraw->setName(string("Board"));
	toDraw->setPosition(parent->getHeight() / 16.0, parent->getWidth()/2-parent->getHeight()*13.0/16.0);
	for (int i = 0; i < 3; i++)
	{
		floors[i] = new FloorObserver(&(*b)[i], toDraw);
	}
	parent->addObject(toDraw);
	board->attach(this);
}

void
BoardObserver::update()
{
	for (auto & f : floors)
		f->update();
}