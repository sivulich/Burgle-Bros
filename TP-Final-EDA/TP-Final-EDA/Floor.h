#pragma once
#include "Configs.h"
#include "TileFactory.h"
//#include "Guard.h"
//#include "GuardDeck.h"

class Floor
{
public:
	/**
		Constructor
		@param w width of the floor
		@param h height of the floor
		@param n number of the floor
	*/
	Floor(int w, int h, int n) : tiles(w,vector<Tile*>(h,nullptr)), floorNumber(n) {};

	/**
		Access a specific tile
		@param col Column of the tile
		@param row Row of the tile
	*/
	Tile * tile(int col, int row);


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
		Receives a matrix of adjacency lists and copies it to the class
		@param a Matrix of adjacency list
	*/
	void setAdjacent(vector<Coord> a[4][4]);

	/**

	*/
//	Coord guardPos() { return guard.getPos(); };


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
		Checks all tiles in the floor for an alarm ringin and
		returns a vector with all the coordenates
	*/
	vector<Coord>& getAlarms();

	/**
		Adds an alarm to a tile
	*/
	void addAlarm(Coord c);

	/**
		If debug verbose defined print the floor in console
	*/
	void print();

private:
	// Matrix of pointers to the base class Tile
	vector<vector<Tile*>> tiles;

	// Floor number
	int floorNumber;

	//
	//Guard guard;

	//
	//GuardDeck guardDeck;

	//Vector of alarms positions
	vector<Coord> alarms;

	//Adjacency map of the floor (only walls, no conection with other floors)
	vector<Coord> adjacent[4][4];

	// Position of the stair token
	Coord stairToken;
};