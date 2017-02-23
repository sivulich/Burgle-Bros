#pragma once
#include "Configs.h"
class actionNode
{
public:
	Coord tilePos;		// column-row-floor number array from the tile the action occured 
	string myAction;
	/**
		Creates an action node
	*/
	actionNode();
	/**
		Set the action node data with the tile (COL-ROW-FLOOR) and action string
	*/
	void setData(int col, int row, int floor, string action);
	/**
		Sets true to know the action was sent.
	*/
	void setSentOk() { sent = true; };

	/**
		Returns true if the action was already sent.
	*/
	bool isSent() { return sent; };
private:
	bool sent;
};

