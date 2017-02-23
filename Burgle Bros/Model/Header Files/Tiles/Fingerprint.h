#pragma once
#include "Tile.h"

/*
Fingerprint is the trickiest Alarm, An alarm goes off when you enter unless you spend a Hack
Token from the Fingerprint Computer Room.
*/


class Fingerprint :
	public Tile
{
public:
	Fingerprint(int floor, int col, int row) : Tile(floor, col, row) {};
	~Fingerprint();

	virtual void enterTile(Player p) override;
};

