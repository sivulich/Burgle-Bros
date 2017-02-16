#include "FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* p)
{
	floor = f;
	parent = p;
	//400 es el height para probar , despues tenemos que definir alguna relacion con el container padre
	floorGrid = new Container(double(parent->getHeight())/1.5, double(parent->getHeight()) / 1.5);
	floorGrid->setName(string("Floor") + to_string(floor->getNumber()));
	//Y ver la poscion dentro del board
	floorGrid->setPosition(0, parent->getWidth()/3*floor->getNumber());
	parent->addObject(floorGrid);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tiles[i][j] = new TileObserver(floor->tile(i,j), floorGrid);
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