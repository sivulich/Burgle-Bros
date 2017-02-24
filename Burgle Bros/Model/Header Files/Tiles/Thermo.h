#pragma once
#include "Tile.h"

/*
If you end your actions on a Thermo tile an alarm will go off. If you are moved here during other turns,
it does not trigger.
*/

// SI EL USUARIO PASA O TERMINA SU TURNO, EL MODELO DEBE CHECKEAR SI PLAYER ESTA EN UNA THERMO TILE
// EN ESE CASO HACE SONAR LA ALARMA

class Thermo :
	public Tile
{
public:
	Thermo(int floor, int col, int row) : Tile(floor, col, row) { };
	~Thermo();
};

