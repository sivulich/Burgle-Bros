#include "FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* floors)
{
	floor = f;
	parent = floors;
	//400 es el height para probar , despues tenemos que definir alguna relacion con el container padre
	floorGrid = new Container(double(parent->getHeight())/1.5, double(parent->getHeight()) / 1.5);
	floorGrid->setName(string("Floor") + to_string(floor->getNumber()));
	//Y ver la poscion dentro del board
	floorGrid->setPosition(0, double(parent->getWidth())/3.0*floor->getNumber());
	parent->addObject(floorGrid);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Floor& fl = *f;
			tiles[i][j] = new TileObserver(fl[i][j], floorGrid);
		}
	}
}

void
FloorObserver::update()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tiles[i][j]->update();
		}
	}

}