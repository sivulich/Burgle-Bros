#pragma once
#include <Configs.h>
#include "../src/Tiles/TileFactory.h"
#include <Guard.h>
#include "../src/PatrolCardDeck.h"
#include "../src/PlayerInterface.h"

class Floor : public BaseModel
{
public:
	/**
		Constructor
		@param n number of the floor
	*/
	Floor(int n, PlayerInterface * p1, PlayerInterface * p2) :tiles(F_WIDTH, vector<Tile *>(F_HEIGHT, nullptr)), guardDeck(n), guard(n, &guardDeck, p1, p2)
	{
		floorNumber = n;
		guard.setAlarms(&alarms);
	};
	/*
	Floor(int w, int h, int n) : tiles(w, vector<Tile*>(h, nullptr)), guardDeck(n)
	{

		guardDeck.createDeck(n);
		guard.setDeck(&guardDeck);
		guard.setAlarms(&alarms);
	};*/

	/**
		Access a specific tile
		@param col Column of the tile
		@param row Row of the tile
	*/
	Tile * tile(int col, int row);
	/**
		Sets current floor and give floor´s guard all active alarms locations.
	*/
	void setNumber(int n)
	{
		floorNumber = n;

		//guard.setDeck(&guardDeck);
		guard.setAlarms(&alarms);
	}
	/**
		Another way to access, with operator []
	*/
	vector<Tile*>& operator[] (unsigned i);
	/**
		Set a specific tile of type t in coord
		@param col Column of the tile
		@param row Row of the tile
		@param t type of the tile
	*/
	void setTile(int col, int row, tileType t);
	/**
		Add vector of tiles to floor
		@param t Vector with the 16 tileTypes for the floor
	*/
	void setTiles(vector<tileType> t);
	/**
		Returns the number of the floor
	*/
	int number();
	/**
		Moves the guard of the floor
	*/
	bool moveGuard();
	/**
		Receives a matrix of adjacency lists and copies it to the class
		@param a Matrix of adjacency list
	*/
	void setMap(vector<Coord> a[F_WIDTH][F_HEIGHT]);
	/**
		Returns guard position in current floor (Coord)
	*/
	Coord guardPos() { return guard.getPos(); };
	/**
		Returns the guard of the floor
	*/
	Guard* getGuard() { return &guard; };
	/**
		Sets the position of the stair token
		@param pos Position of the stair in the floor below
	*/
	void setStairToken(Coord pos);
	/**
		Return the position of the stair token
	*/
	Coord stairPos() { return stairToken; };
	/**
		Checks all tiles in the floor for an alarm ringing and
		returns a vector with all the coordenates
	*/
	vector<Coord>& getAlarms();
	/**
		Adds an alarm to a tile
	*/
	void addAlarm(Coord c);
	/**
		Returns the patrol card deck associated with the current floor
	*/
	PatrolCardDeck* getPatrolDeck() { return &guardDeck; };
	/**
		If debug verbose defined print the floor in console
	*/
	void print();
	/**
		Given a coordinate adds tiles found up, right, left and down to adjacency list no matter if walls are found in between
	*/
	void getThroughWalls(Coord c, list<Tile*>* adj);

private:
	// Matrix of pointers to the base class Tile
	vector<vector<Tile*>> tiles;

	// Floor number
	int floorNumber;

	// Guar patrolling on the floor
	Guard guard;

	// Deck with patrol cards
	PatrolCardDeck guardDeck;

	//Vector with alarms positions
	vector<Coord> alarms;

	//Adjacency map of the floor (only walls, no conection with other floors)
	vector<Coord> adjacent[F_WIDTH][F_HEIGHT];

	// Position of the stair token
	Coord stairToken;
};