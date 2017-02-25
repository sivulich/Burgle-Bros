#include "../../Header Files/Tiles/Foyer.h"


Foyer::~Foyer()
{
}

void Foyer::enterTile(PlayerInterface * player) {
	

	Coord temp(floor(), col(), row());

	//Add the tiles surrounding the tile to the player's visibleFrom list
	if (!(temp.row == 0))	//if its not the first row
		player->addVisibleTile(Coord(temp.floor, temp.col, temp.row - 1));
	if(!(temp.row == 3))	// if its not the last row
		player->addVisibleTile(Coord(temp.floor, temp.col, temp.row + 1));
	if(!(temp.col == 0))	// if its not the first column
		player->addVisibleTile(Coord(temp.floor, temp.col - 1, temp.row ));
	if (!(temp.col == 3))	// if its not the last column
		player->addVisibleTile(Coord(temp.floor, temp.col + 1, temp.row));

}
