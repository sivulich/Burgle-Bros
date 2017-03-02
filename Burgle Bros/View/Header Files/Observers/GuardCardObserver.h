#pragma once
#include "Observer.h"
#include "../../../Model/Header Files/PatrolCard.h"
#include "../Image.h"
#include "../Container.h"
class GuardCardObserver:public Observer
{
public:
	GuardCardObserver(Container* p, BaseCard* card);
	void update();
	void setCard(BaseCard* card);
	void setPos(int y, int x) { this->y = y; this->x = x; front->setPosition(y, x); back->setPosition(y, x); };
	void setOn(bool b);
	bool isClicked() { if (on == false) return false; if (drawFront == true) return front->isClicked(); return back->isClicked(); };
	~GuardCardObserver();
private:
	Container* parent;
	Image * back;
	Image * front;
	BaseCard* card;
	bool drawFront,on;
	int y, x;
};

