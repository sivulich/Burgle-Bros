#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
/*
Stairs allow you to move directly up one oor. Put
a Downstairs token on the corresponding tile one oor up
(I.e. 2nd row, 3rd column). You can also peek up stairs and come
back downstairs. It takes 1 action to take the stairs to the roof
at the end of the game.
*/

// DE LAS STAIRS SE ENCARGA EL MODELO CUANDO SE LAS DA VUELTA
class Stair :
	public Tile
{
public:
	Stair(int floor, int col, int row) : Tile(STAIR,floor, col, row) {};
	~Stair();
};

