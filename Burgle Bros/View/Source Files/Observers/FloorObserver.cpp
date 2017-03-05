#include "../../Header Files/Observers/FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* floors)
{
	floor = f;
	parent = floors;
	//400 es el height para probar , despues tenemos que definir alguna relacion con el container padre
	floorGrid = new Container(parent->getWidth(), parent->getWidth());
	floorGrid->setName(string("Floor") + to_string(floor->number()));
	//Y ver la poscion dentro del board
	floorGrid->setPosition(0, 0);
	parent->addObject(floorGrid);
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

}

void
FloorObserver::update()
{
	deck->update();
}