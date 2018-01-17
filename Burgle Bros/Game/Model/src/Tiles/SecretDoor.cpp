#include ".././Tiles/SecretDoor.h"

SecretDoor::~SecretDoor()
{
}


void SecretDoor::turnUp() {
	Tile::turnUp();
	for ( vector<Tile *>::iterator it = secretDoors.begin(); it != secretDoors.end(); it++) {
		(*it)->addAdjacent(getPos());
		DEBUG_MSG("Added the secret door to the tile " << (*it)->getPos());
	}
}