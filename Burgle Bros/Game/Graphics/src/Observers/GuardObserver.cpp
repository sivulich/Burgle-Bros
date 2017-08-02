#include "./GuardObserver.h"

GuardObserver::GuardObserver(Guard* g, Container* pa)
{
	parent = pa;
	guard = g;
	guardIm = new Image(string("../View/Images/Guard.png"));
	dices.resize(7);
	guardIm->setScale(0.45*pa->getWidth() / 4 / guardIm->getHeight());
	guardIm->setPosition((guard->getPos().row)*parent->getHeight() / 4 + 0.9* parent->getHeight() / 4 - guardIm->getScale()*guardIm->getHeight(), guard->getPos().col*parent->getWidth() / 4 + 0.45*parent->getWidth() / 4 - guardIm->getScale()*guardIm->getWidth() / 2);
	for (int i = 1; i <= 6; i++)
	{
		dices[i] = new Image(string("../View/Images/Dices/White ") + to_string(i) + string(".png"));
		dices[i]->setScale(0.2*pa->getWidth() / 4 / dices[i]->getWidth());
	}
	parent->addObject(guardIm);
	guard->attach(this);
	lastSpeed = 0;
}

void
GuardObserver::update()
{
	if (guard->getSpeed() <= 6)
	{
		if (lastSpeed != guard->getSpeed())
		{
			parent->removeObject(dices[lastSpeed]);
			parent->addObject(dices[guard->getSpeed()]);
			lastSpeed = guard->getSpeed();
		}
	}
	else
		cout << "Speed is wrong speed is " << guard->getSpeed() << endl;
	dices[lastSpeed]->setPosition(guard->getTarget().row*parent->getWidth() / 4 + 0.45*parent->getWidth() / 4 - dices[lastSpeed]->getScale()*dices[lastSpeed]->getWidth() / 2, guard->getTarget().col*parent->getWidth() / 4 + 0.45*parent->getWidth() / 4 - dices[lastSpeed]->getScale()*dices[lastSpeed]->getHeight() / 2);
	guardIm->deleteAnimation();
	pair<int, int> init(guardIm->getPos().first, guardIm->getPos().second),finish((guard->getPos().row)*parent->getHeight() / 4 + 0.9* parent->getHeight() / 4 - guardIm->getScale()*guardIm->getHeight(), guard->getPos().col*parent->getWidth() / 4 + 0.45*parent->getWidth() / 4 - guardIm->getScale()*guardIm->getWidth() / 2);
	if (guardIm->getPos().first>=parent->getWidth())
		guardIm->setPosition(finish.first, finish.second);
	else
		guardIm->addAnimation(new MoveAnimation(finish, 0.2));
}