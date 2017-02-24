#include "../../Header Files/Tiles/Walkway.h"


Walkway::~Walkway()
{
}

void Walkway::enterTile(void * player) {
	if (isFlipped() == false) {
		if (floor() != 0) {		// if the card is flipped down and not the first floor
			turnUp();
			fallDown((Player *)player);		// throw the player to the tile beneath
			setAdjacent(Coord(floor() - 1, col(), row()));
		}
		else if (floor() == 0)
			turnUp();
	}
}

bool Walkway::fallDown(Player * p) {
	if (floor() != 0)				// if not on the bottom floor
		p->changePos(Coord(floor() - 1, col(), row()));		//move the player to the floor beneath it
}
