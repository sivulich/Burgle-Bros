#pragma once
#include "../Model/Header Files/Board.h"
#include "../Container.h"
#include "FloorObserver.h"
#include "Observer.h"
class BoardObserver:public Observer{
public:
	BoardObserver(Board* b, Container* c);
	Container* getFloor(int i) { return floors[i]->getFloorGrid(); };
	void update();
private:
	FloorObserver* floors[3];
	Container* toDraw;
	Board* board;
	Container* parent;
};