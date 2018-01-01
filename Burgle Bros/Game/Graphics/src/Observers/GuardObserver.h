#pragma once

#include <Guard.h>
#include <Floor.h>
#include <Container.h>
#include "./Observer.h"
#include "../Graphic Objects/Image.h"

class GuardObserver:public Observer
{
public:
	GuardObserver(Guard* g, Container* c,int floorNumber);	
	bool guardIsMoving() { return guardIm->hasAnimation(); };
	void update();
	void reset();
private:
	Guard* guard;
	Container* boardCont;
	Image* guardIm;
	int floorNumber;
	vector<Image*> dices;
	unsigned lastSpeed;
	Coord lastPos;
	Coord lastTarget;

};
