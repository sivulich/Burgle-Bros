#pragma once
#include "../Header Files/Configs.h"
#include "../Header Files/Floor.h"
#include "../Header Files/Loots/Loot.h"
#include "../Header Files/Tiles/Tile.h"

// Define the roof position
#define ROOF Coord(3,0,0)

class Board: public BaseModel
{
public:
	Board();
	~Board();

	void print();
	/**
		Returns the floor i
	*/
	Floor& operator[](size_t i) { return floor[i]; };
	/**
		Return the a tile in the board
	*/
	Tile * getTile(Coord c);

	/**
		Sets board tiles randomly
	*/
	void setBoard();

	/**
		Sets board with defined tiles (order In vector (1,A1) (1,B1) (1,C1) ... (2,A1) (2,B1) (2,C1))
	*/
	void setBoard(vector<tileType> tiles);

	/**
		Set adjacency between tiles
	*/
	void setWalls();

	// Parse the board and set things in tiles depending on its type. Should be called after setting the board and walls
	void parseBoard();
private:
	

	// Sets the vector of tiles the safe needs to be cracked 
	void prepSafeTile(Safe * safe);

	Floor floor[3];
	// MAPA: QUIZAS AL PEDO EN EL BOARD VER SI SE PUEDE BORRAR
	vector<Coord> adjacent[3][4][4];
};



