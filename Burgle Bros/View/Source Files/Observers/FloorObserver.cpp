#include "../../Header Files/Observers/FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* floors)
{
	floor = f;
	parent = floors;
	//400 es el height para probar , despues tenemos que definir alguna relacion con el container padre
	floorGrid = new Container(double(parent->getHeight())*13.0/16.0, double(parent->getHeight()) *13.0/ 16.0);
	floorGrid->setName(string("Floor") + to_string(floor->number()));
	//Y ver la poscion dentro del board
	floorGrid->setPosition(0, double(parent->getWidth())/3.0*floor->number());
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