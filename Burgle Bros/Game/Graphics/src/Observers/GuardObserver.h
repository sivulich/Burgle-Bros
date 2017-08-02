#pragma once

#include <Guard.h>
#include "./Observer.h"
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Image.h"
#include "../Animations/MoveAnimation.h"

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
