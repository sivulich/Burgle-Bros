#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
/*
You may move into this tile through walls adjacent to this tile. is is one-way; you can’t move or peek
back out through a wall. Guards will not move through secret doors.
*/

// CUANDO SE REVELA UNA SECRET DOOR, EL MODELO DEBE AGREGAR A LAS 4 TILES ADJACENTES LA POSICION DE LA SECRET DOOR 
// A SUS RESPECTIVAS TILES ADJACENTES. A SECRET DOOR NO SE LE CAMBIA NADA

class SecretDoor :
	public Tile
{
public:
	SecretDoor(int floor, int col, int row) : Tile(floor, col, row) {};
	~SecretDoor();
};

