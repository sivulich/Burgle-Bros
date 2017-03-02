#include "../../Header Files/Tiles/Walkway.h"


Walkway::~Walkway()
{
}

void Walkway::enterTile(PlayerInterface * player)
{
	if (isFlipped() == false && floor() != 0) {		// if the card is flipped down and not the first floor
		turnUp();
		fallDown(player);		// throw the player to the tile beneath
	}
	else		// any other case, enter the tile normally
		Tile::enterTile(player);
}

bool Walkway::fallDown(PlayerInterface * player)
{
	if (floor() != 0) {			// if not on the bottom floor
		player->setPosition(Coord(floor() - 1, col(), row()));		//move the player to the floor beneath it
		player->updateVisibleFrom();
		return true; 
	}
	else
		return false;
}
