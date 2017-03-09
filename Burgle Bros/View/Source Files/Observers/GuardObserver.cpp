#include "../../Header Files/Observers/GuardObserver.h"

GuardObserver::GuardObserver(Guard* g, Container* pa)
{
	parent = pa;
	guard = g;
	guardIm = new Image(string("../View/Images/Guard.png"));
	guardIm->setScale(0.45*pa->getWidth() / 4/guardIm->getHeight());
	guardIm->setPosition((guard->getPos().row)*parent->getHeight() / 4+0.9* parent->getHeight() / 4 -guardIm->getScale()*guardIm->getHeight(), guard->getPos().col*parent->getWidth() / 4+0.45*parent->getWidth() / 4 -guardIm->getScale()*guardIm->getWidth()/2);
	parent->addObject(guardIm);
	guard->attach(this);
}

void
GuardObserver::update()
{
	reset();
	guardIm->deleteAnimation();
	pair<int, int> init(guardIm->getPos().first, guardIm->getPos().second),finish((guard->getPos().row)*parent->getHeight() / 4 + 0.9* parent->getHeight() / 4 - guardIm->getScale()*guardIm->getHeight(), guard->getPos().col*parent->getWidth() / 4 + 0.45*parent->getWidth() / 4 - guardIm->getScale()*guardIm->getWidth() / 2);
	if (guardIm->getPos().first>=parent->getWidth())
		guardIm->setPosition(finish.first, finish.second);
	else
		guardIm->addAnimation(new MoveAnimation(init, finish, 0.4));
}