#pragma once
#include "Configs.h"
#include "TileFactory.h"
//#include "Guard.h"
//#include "GuardDeck.h"

class Floor
{
public:
	/**
		Default constructor
	*/
	Floor(int w, int h, int n) : tiles(w,vector<Tile*>(h,nullptr)), floorNumber(n) {};

	/**
		Acces a tile in coord (COL,ROW)
	*/
	Tile * tile(int i, int j)
	{
		return tiles[i][j];
	};

	/**
		
	*/
	vector<Tile*>& operator[] (unsigned i)
	{
		return tiles[i];
	};

	/**
		Set a specific tile of type t in coord (COL,ROW) 
	*/
	void setTile(int col, int row, tileType t)
	{

		tiles[col][row] = TileFactory().newTile(t,col,row);

	};

	/**
		Add tiles to floor
		@param t Vector with the 16 tileTypes for the floor
	*/
	void setTiles(vector<tileType> t)
	{
		if (t.size() == 16)
		{
			for (int j = 0; j < 16; j++)
				setTile(j % 4, j / 4, t[j]);
		}		
	};

	/**

	*/
	int getNumber()
	{
		return floorNumber;
	};

	void setAdjacent(vector<Coord> a[4][4])
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				adjacent[i][j] = a[i][j];	
	}

	/**

	*/
//	Coord guardPos() { return guard.position(); };

	/**

	*/
	Coord stairPos() { return stairToken; };

	/**

	*/
	vector<Coord>& getAlarms() { return alarmTokens; };

	void print()
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
				cout << toString(tiles[i][j]->getType()) << " ";
			cout << endl;
		}
	};

private:
	vector<vector<Tile*>> tiles;
	int floorNumber;
	//Guard guard;
	//GuardDeck guardDeck;
	vector<Coord> alarmTokens;
	vector<Coord> adjacent[4][4];
	Coord stairToken;
};