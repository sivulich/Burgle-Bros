#include "../../Header Files/Observers/GuardCardObserver.h"



GuardCardObserver::GuardCardObserver(Container* p,BaseCard* card)
{
	parent = p;
	y = x = 0;
	back = new Image(string("../View/Images/Patrol/PC R.png"));
	back->setPosition(y, x);
	back->setScale(double(parent->getHeight()) / double(back->getHeight()));
	this->card = card;
	front = new Image(string("../View/Images/Patrol/PC ") + card->getDescription() + ".png");
	front->setPosition(y, x);
	front->setScale(double(parent->getHeight()) / double(front->getHeight()));
	if (card->isFlipped() == false)
		p->addObject(back);
	else
		p->addObject(front);
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
		on = false;
	}
	else
	{

		if (card->isFlipped() == true && parent->contains(front)==false)
			parent->addObject(front);
		else if (parent->contains(back) == false)
			parent->addObject(back);
		on = true;
	}
}
void
GuardCardObserver::update()
{
	if (on == false)
	{
		parent->removeObject(front);
		parent->removeObject(back);
		return;
	}
	else if (card->isFlipped() == true && parent->contains(front)==false)
	{
		parent->removeObject(back);
		parent->addObject(front);
	}
	else if (card->isFlipped() == false && parent->contains(back) == false)
	{
		parent->removeObject(front);
		parent->addObject(back);
	}
}
void
GuardCardObserver::setCard(BaseCard* card)
{
	if (card == this->card)
	{
		return;
	}
	parent->removeObject(front);
	parent->removeObject(back);
	if (front != nullptr)
		delete front;
	front = new Image(string("./Images/Patrol/PC ") + card->getDescription() + ".png");
	front->setPosition(y, x);
	front->setScale(double(parent->getHeight()) / double(front->getHeight()));	
	if (card->isFlipped() == true)
		parent->addObject(front);
	else
		parent->addObject(back);
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
