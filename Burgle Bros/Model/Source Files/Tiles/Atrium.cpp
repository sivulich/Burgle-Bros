#include "../../Header Files/Tiles/Atrium.h"



void Atrium::enterTile(PlayerInterface * player) {

	Tile::enterTile(player);
	Coord tempCoord;
	tempCoord.col = col();				//set the new tile to the same positition as the atrium tile
	tempCoord.row = row();

	if (getPos().floor != 0) {					// if not on the bottom floor
		tempCoord.floor = floor ()- 1;	//add the floor beneath it
		player->addVisibleTile(tempCoord);
	}
	if (getPos().floor != 2) {					//if not on the top floor
		tempCoord.floor = floor() + 1;	//add the floor above it
		player->addVisibleTile(tempCoord);
	}


}
