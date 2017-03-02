#include "../../Header Files/Tiles/Walkway.h"


Walkway::~Walkway()
{
}

void Walkway::enterTile(PlayerInterface * player)
{
	Tile::enterTile(player);
	if (isFlipped() == false) {
		if (floor() != 0) {		// if the card is flipped down and not the first floor
			this->turnUp();
			fallDown(player);		// throw the player to the tile beneath
			addAdjacent(Coord(floor() - 1, col(), row()));
		}
		else if (floor() == 0)
			turnUp();
	}
}

bool Walkway::fallDown(PlayerInterface * player)
{
	if (floor() != 0)				// if not on the bottom floor
		player->setPosition(Coord(floor() - 1, col(), row()));		//move the player to the floor beneath it
	return true; //!!!!!!!!!!!!!!!!!!!!!!!
}
