#include "../../Header Files/Tiles/Walkway.h"


Walkway::~Walkway()
{
}

void Walkway::enterTile(void * player)
{
	Player * p = (Player *)player;
	if (floor() > 0) p->changePos(Coord(floor() - 1, col(), row()));
}
