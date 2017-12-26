#pragma once

#include <Guard.h>
#include <Floor.h>
#include <Container.h>
#include "./Observer.h"
#include "../Graphic Objects/Image.h"
#include "../Animations/MoveAnimation.h"
#include "../Animations/FadeAnimation.h"
class GuardObserver:public Observer
{
public:
	GuardObserver(Guard* g, Container* c, double tileSize, pair<int, int> positions[4][4]);	
	void update();
	void reset();
private:
	Guard* guard;
	Container* floor;
	Image* guardIm;
	pair<int, int> positions[4][4];
	vector<Image*> dices;
	unsigned lastSpeed;
	Coord lastPos;
	Coord lastTarget;

};
