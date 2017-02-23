#pragma once

#include "Tile.h"

class ServiceDuct : public Tile
{
public:
	ServiceDuct();
	~ServiceDuct();

	/**
		Points this tile to the other side of the duct
	*/
	void setOtherSide(ServiceDuct* t);

	/**
		Check if the other side of the duct has been revealed
	*/
	bool isOpen();
private:
	ServiceDuct* otherSide;
};

