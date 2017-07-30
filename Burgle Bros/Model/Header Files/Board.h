#pragma once
#include "../Header Files/Configs.h"
#include "../Header Files/Floor.h"
#include "../Header Files/Loots/Loot.h"
#include "../Header Files/Tiles/Tile.h"
#include "../Header Files/PlayerInterface.h"
// Define the roof position
#define ROOF Coord(3,0,0)

class Board: public BaseModel
{
public:
	Board(PlayerInterface* p1, PlayerInterface* p2);
	~Board();

	void print();
	/**
		Returns the floor i
	*/
	Floor& operator[](size_t i) { return *floor[i]; };
	/**
		Return the a tile in the board
	*/
	Tile * getTile(Coord c);
	 /**
	 
	 */
	Guard * getGuard(unsigned int f){if (f < 3) return floor[f]->getGuard();
	}

	PatrolCardDeck * getDeck(unsigned int f) {
		if (f < 3) return floor[f]->getPatrolDeck();
	}
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

	void adjThroughWalls(Coord c, list<Tile*>* adj) { if (c.floor < 4) floor[c.floor]->getThroughWalls(c, adj); };
private:
	// Sets the vector of tiles the safe needs to be cracked 
	void prepSafeTile(Safe * safe);

	Floor* floor[3];
	// MAPA: QUIZAS AL PEDO EN EL BOARD VER SI SE PUEDE BORRAR
	vector<Coord> adjacent[3][4][4];
};



