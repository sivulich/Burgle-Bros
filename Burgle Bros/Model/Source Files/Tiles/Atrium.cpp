#include "../../Header Files/Tiles/Atrium.h"

Atrium::~Atrium()
{
}

void Atrium::enterTile(void * player) {
	Player * p = (Player *)player;

	Coord tempCoord;
	tempCoord.col = col();				//set the new tile to the same positition as the atrium tile
	tempCoord.row = row();

	if (getPos().floor != 0) {					// if not on the bottom floor
		tempCoord.floor = floor ()- 1;	//add the floor beneath it
		p->addVisibleTile(tempCoord);
	}
	if (getPos().floor != 2) {					//if not on the top floor
		tempCoord.floor = floor() + 1;	//add the floor above it
		p->addVisibleTile(tempCoord);
	}


}
