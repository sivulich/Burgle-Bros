#include "./FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* boardContainer)
{
	floor = f;
	this->boardContainer = boardContainer;

	floorContainer = new Container(FLOOR_HEIGHT, FLOOR_WIDTH, "Floor " + to_string(floor->number()) + " container");
	floorContainer->setOnlyChildClickable(true);
	floorContainer->setHoverable(false);

	// Set position in board
	floorContainer->setPosition(FLOOR_YPOS, FLOOR_XPOS[floor->number()]);

	boardContainer->addObject(floorContainer);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Floor& fl = *f;
			tiles[i][j] = new TileObserver(fl[i][j], floorContainer);
			if (fl[i][j]->is(SAFE))
				safe = fl[i][j];
			fl[i][j]->attach(this);
		}
	}
	safeIsFlipped = false;
	// Attach to floor model
	floor->attach(this);



	guard = new GuardObserver(floor->getGuard(), boardContainer, floor->number());
	deck = new GuardDeckObserver(f, boardContainer);
}

void FloorObserver::update()
{
	//	deck->update();
	if (safeIsFlipped != safe->isFlipped())
	{
		safeIsFlipped = safe->isFlipped();
		int col = safe->getPos().col;
		int row = safe->getPos().row;

		for (int i = 0; i < 4; i++)
			if (i != row)
				tiles[col][i]->showSafeNumber();

		for (int j = 0; j < 4; j++)
			if (j != col)
				tiles[j][row]->showSafeNumber();

	}

}