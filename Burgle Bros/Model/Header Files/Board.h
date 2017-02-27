#pragma once
#include "../Header Files/Configs.h"
#include "../Header Files/Floor.h"
#include "../Header Files/Loots/Loot.h"
#include "../Header Files/Tiles/Tile.h"

class Board, public BaseModel
{
public:
	Board();
	~Board();

	void print();
	/**
		Returns the floor i
	*/
	Floor* operator[](size_t i) { return floor[i]; };
	Tile * getTile(Coord c);
private:
	Floor* floor[3];
	// MAPA: QUIZAS AL PEDO EN EL BOARD VER SI SE PUEDE BORRAR
	vector<Coord> adjacent[3][4][4];
};



