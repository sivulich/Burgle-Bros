#pragma once
#include "../../Model/Header Files/Board.h"
#include "../Header Files/Container.h"
#include "../Header Files/Observers/FloorObserver.h"
#include "../Header Files/Observers/observer.h"

class BoardObserver:public Observer{
public:
	BoardObserver(Board* b, Container* c);
	Container* getFloor(int i) { return floors[i]->getFloorGrid(); };
	FloorObserver& operator[](size_t i) { return *(floors[i]); };
	void update();
private:
	FloorObserver* floors[3];
	Container* toDraw[3];
	Board* board;
	Container* parent;
};