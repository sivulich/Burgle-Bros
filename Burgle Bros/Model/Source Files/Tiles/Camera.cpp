#include "../../Header Files/Tiles/Camera.h"

Camera::~Camera()
{
	
}

void Camera::enterTile(PlayerInterface * player) {
	Tile::enterTile(player);
	for (int i = 0; i < otherCameras.size(); i++)
	{
		if (otherCameras[i]->isFlipped() == true) {			// if the other camera is flipped up
			player->addVisibleTile(otherCameras[i]->getPos());	// then add that tile to the player's visible from tiles
			DEBUG_MSG("You can be seen from camera tile " << otherCameras[i]->getPos());
		}
	}
}
