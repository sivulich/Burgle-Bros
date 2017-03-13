#include "../../Header Files/Observers/FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* floors)
{
	floor = f;
	parent = floors;
	//400 es el height para probar , despues tenemos que definir alguna relacion con el container padre
	floorGrid = new Container(parent->getWidth(), parent->getWidth());
	secondGrid = new Container(parent->getWidth(), parent->getWidth());
	secondGrid->setOnlyChildClickable(true);
	secondGrid->setHoverable(false);
	floorGrid->setName(string("Floor") + to_string(floor->number()));
	//Y ver la poscion dentro del board
	floorGrid->setPosition(0, 0);
	secondGrid->setPosition(0, 0);
	parent->addObject(floorGrid);
	parent->addObject(secondGrid);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Floor& fl = *f;
			tiles[i][j] = new TileObserver(fl[i][j], floorGrid);
		}
	}
	floor->attach(this);
	deck = new GuardDeckObserver(f, floors);
	guard = new GuardObserver(floor->getGuard(), secondGrid);
}

void
FloorObserver::update()
{
	deck->update();
	//guard->reset();
	//guard->update();
}