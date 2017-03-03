#pragma once

#include "Tile.h"
#include "../PlayerInterface.h"
class ServiceDuct : public Tile
{
public:
	ServiceDuct(int floor, int col, int row) : Tile(SERVICE_DUCT, floor, col, row) { isConnected = false; };
	~ServiceDuct();

	/**
		Points this tile to the other side of the duct
	*/
	void setOtherSide(ServiceDuct* t);

	/**
	Executes the tile's special actions, if any...
	@param p player who is moving
	*/
	virtual void enterTile(PlayerInterface * player) override;

	/**
		Check if the other side of the duct has been revealed
	*/
	bool isOpen();
private:
	ServiceDuct* otherSide;
	bool isConnected;
};

