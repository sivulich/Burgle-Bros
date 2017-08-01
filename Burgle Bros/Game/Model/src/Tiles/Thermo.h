#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"

/*
If you end your actions on a Thermo tile an alarm will go off. If you are moved here during other turns,
it does not trigger.
*/

// SI EL USUARIO PASA O TERMINA SU TURNO, EL MODELO DEBE CHECKEAR SI PLAYER ESTA EN UNA THERMO TILE
// EN ESE CASO HACE SONAR LA ALARMA

class Thermo :
	public Tile
{
public:
	Thermo(int floor, int col, int row) : Tile(THERMO,floor, col, row) { };
	~Thermo();
};

