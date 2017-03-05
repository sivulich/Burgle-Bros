#include "../../Header Files/Tiles/ServiceDuct.h"





ServiceDuct::~ServiceDuct()
{
}

void ServiceDuct::setOtherSide(ServiceDuct* t)
{
	otherSide = t;
}


bool ServiceDuct::isOpen()
{
	return otherSide->isFlipped();
}

void ServiceDuct::enterTile(PlayerInterface * player) {
	Tile::enterTile(player);
	if (isOpen() && isConnected == false ) {
		addAdjacent(otherSide->getPos());
		otherSide->addAdjacent(getPos());
		otherSide->isConnected = true;
		isConnected = true;
		DEBUG_MSG("Now you can move to the tile " << otherSide->getPos());

	}
}