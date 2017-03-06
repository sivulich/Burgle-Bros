#include "../../Header Files/Tiles/Walkway.h"


Walkway::~Walkway()
{
}

void Walkway::enterTile(PlayerInterface * player)
{
	if (isFlipped() == true && floor() != 0) //ANDA CON ESTO, NO SE QUE ONDA, ARREGLENLO PERROS
	{		// if the card is flipped down and not the first floor
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

		updateVisibleFrom(player);
		DEBUG_MSG("You stepped into a walkway and fell down a floor.");
		return true; 
	}
	else {
		DEBUG_MSG("You stepped into a walkway. Luckily you were on the first floor.");
		return false;
	}
}
