#include "../../Header Files/Observers/GuardCardObserver.h"



GuardCardObserver::GuardCardObserver(Container* p,BaseCard* card)
{
	parent = p;
	y = x = 0;
	drawFront = false;
	back = new Image(string("../View/Images/Patrol/PC R.jpg"));
	back->setPosition(y, x);
	back->setScale(double(parent->getHeight()) / double(back->getHeight()));
	this->card = card;
	front = new Image(string("../View/Images/Patrol/PC ") + card->getDescription() + ".jpg");
	front->setPosition(y, x);
	front->setScale(double(parent->getHeight()) / double(front->getHeight()));
	p->addObject(back);
	on = true;
	card->attach(this);
}
void
GuardCardObserver::setOn(bool b)
{
	if (b == on)
		return;
	if (b == false)
	{
		parent->removeObject(back);
		parent->removeObject(front);
		on = b;
	}
	else
	{
		drawFront = card->isFlipped();
		if (drawFront == true)
			parent->addObject(front);
		else
			parent->addObject(back);
	}
}
void
GuardCardObserver::update()
{
	if (on == false)
	{
		return;
	}
	else if (card->isFlipped() == true && drawFront == false)
	{
		drawFront = true;
		parent->removeObject(back);
		parent->addObject(front);
	}
	else if (card->isFlipped() == false && drawFront == true)
	{
		drawFront = false;
		parent->removeObject(front);
		parent->addObject(back);
	}
}
void
GuardCardObserver::setCard(BaseCard* card)
{
	if (card == this->card)
	{
		drawFront = card->isFlipped();
		return;
	}
	if (drawFront == true)
	{
		parent->removeObject(front);
		parent->addObject(back);
	}	
	if (front != nullptr)
		delete front;
	front = new Image(string("./Images/Patrol/PC ") + card->getDescription() + ".jpg");
	front->setPosition(y, x);
	front->setScale(double(parent->getHeight()) / double(front->getHeight()));	
	drawFront = false;
	this->card = card;
}

GuardCardObserver::~GuardCardObserver()
{
	parent->removeObject(back);
	parent->removeObject(front);
	if(back!=nullptr)
		delete back;
	if (front != nullptr)
		delete front;
}
