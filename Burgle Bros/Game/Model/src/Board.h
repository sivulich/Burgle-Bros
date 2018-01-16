#pragma once
#include "./Configs.h"
#include "./Floor.h"
#include "../src/Loots/Loot.h"
#include <Tile.h>
#include "../src/PlayerInterface.h"
// Define the roof position
#define ROOF Coord(3,0,0)

class Board: public BaseModel
{
public:
	Board(PlayerInterface* p1, PlayerInterface* p2);
	~Board();

	void print();
	/**
		@Returns the floor i 
	*/
	Floor& operator[](size_t i) { return *floor[i]; };
	/**
		@Returns the a tile in the board (Tile *)
	*/
	Tile * getTile(Coord c);
	vector<tileType> getTileSetup();
	 /**
		@Returns the i-th floor guard(Guard *)
	 */
	Guard * getGuard(unsigned int f){if (f < 3) return floor[f]->getGuard();
	}
	/**
	@Returns the i-th floor guard deck(PatrolCardDeck *)
	*/
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
	/** 
		Parse the board and set things in tiles depending on its type. Should be called after setting the board and walls
	*/
	void parseBoard();
	/**
	
	*/
	Floor * getFloor(unsigned f) { if (f < NUMBER_FLOORS) return floor[f]; };
	/**
		Adds tile 'C' to tile´s adjacency list 'adj' despite a wall existing in-between
	*/
	//NO SE ESTA USANDO SE USA PARA ALGUNA TILE EN PARTICULAR????//
	void adjThroughWalls(Coord c, list<Tile*>* adj) { if (c.floor < 4) floor[c.floor]->getThroughWalls(c, adj); };

	/**
		Updates guard in f floor during player turn
	*/
	void updateGuard(unsigned f) { if (f < 3) { floor[f]->updateGuard(); } };
	/**
	
	*/
	void checkGuard(unsigned f) { if (f < 3) { floor[f]->guardChek(); } };

	/**
	
	*/
	void checkOnePlayer(PlayerInterface * p, unsigned f);

	/**
	
	*/
	void checkCameras(Coord c1);

	/**
	
	*/
	vector<Tile *> getCameras() { return cameras; };
private:
	/**
		Sets the vector of tiles the safe needs to be cracked 
	*/
	void prepSafeTile(Safe * safe);

	Floor* floor[3];

	vector<Tile *> cameras;
	// MAPA: QUIZAS AL PEDO EN EL BOARD VER SI SE PUEDE BORRAR
	vector<Coord> adjacent[NUMBER_FLOORS][F_WIDTH][F_HEIGHT];
};



