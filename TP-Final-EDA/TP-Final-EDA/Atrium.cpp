#include "Atrium.h"

Atrium::~Atrium()
{
}

void Atrium::moveTo(Player p) {
	Tile::moveTo(p);							//execute the normal move function 
	Coord tempCoord;
	tempCoord.col = getPos().col;				//set the new tile to the same positition as the atrium tile
	tempCoord.row = getPos().row;

	if (getPos().floor != 0) {					// if not on the bottom floor
		tempCoord.floor = getPos().floor - 1;	//add the floor beneath it
		p.addVisibleTile(tempCoord);
	}
	if (getPos().floor != 2) {					//if not on the top floor
		tempCoord.floor = getPos().floor + 1;	//add the floor above it
		p.addVisibleTile(tempCoord);
	}


}
