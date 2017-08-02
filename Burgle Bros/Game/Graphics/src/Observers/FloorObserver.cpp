#include "./FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* floorContainer)
{
	floor = f;
	parent = floorContainer;
	

	// PORQUE DOS CONTAINERS!!??
	floorGrid = new Container(parent->getWidth(), parent->getWidth());
	secondGrid = new Container(parent->getWidth(), parent->getWidth());
	secondGrid->setOnlyChildClickable(true);
	secondGrid->setHoverable(false);
	floorGrid->setName(string("Floor") + to_string(floor->number()));
	//Y ver la poscion dentro del board

	//parent->setName(string("Floor") + to_string(floor->number()));

	floorGrid->setPosition(0, 0);
	secondGrid->setPosition(0, 0);
	parent->addObject(floorGrid);
	parent->addObject(secondGrid);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Floor& fl = *f;
			tiles[i][j] = new TileObserver(fl[i][j], floorContainer);
		}
	}

	// Attach to floor model
	floor->attach(this);

	deck = new GuardDeckObserver(f, floorContainer);

	guard = new GuardObserver(floor->getGuard(), floorContainer);
}

void
FloorObserver::update()
{
	deck->update();

}