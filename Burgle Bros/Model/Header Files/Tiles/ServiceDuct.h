#pragma once

#include "Tile.h"
#include "../PlayerInterface.h"
class ServiceDuct : public Tile
{
public:
	ServiceDuct(int floor, int col, int row) : Tile(SERVICE_DUCT, floor, col, row) {};
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

