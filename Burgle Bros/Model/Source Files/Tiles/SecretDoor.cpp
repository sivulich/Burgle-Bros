#include "../../Header Files/Tiles/SecretDoor.h"

SecretDoor::~SecretDoor()
{
}


void SecretDoor::enterTile(PlayerInterface * player) {
	Tile::enterTile(player);
	for ( vector<Tile *>::iterator it = secretDoors.begin(); it != secretDoors.end(); it++) {
		(*it)->addAdjacent(getPos());
		DEBUG_MSG("Added the secret door to the tile " << (*it)->getPos());
	}
}