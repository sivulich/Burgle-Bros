#pragma once

#include "../Model/Header Files/Guard.h"
#include "Observer.h"
#include "../Container.h"
#include "../Image.h"
#include "../MoveAnimation.h"

class GuardObserver:public Observer {
public:
	GuardObserver(Guard* g, Container* pa);
	void update();
	void reset() { if (guardIm != nullptr) { parent->removeObject(guardIm); parent->addObject(guardIm); } };
private:
	Container* parent;
	Image* guardIm;
	vector<Image*> dices;
	unsigned lastSpeed;
	Guard* guard;
};
