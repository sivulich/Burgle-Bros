#pragma once
#include "Configs.h"
#include "Tile.h"
//#include "Guard.h"
//#include "GuardDeck.h"

class Floor
{
public:
	/**

	*/
	Floor() : tiles(4,vector<Tile*>(4,nullptr)) {};

	Floor(int n) : floorNumber(n), tiles(4, vector<Tile*>(4, nullptr))
	{
		
	};

	/**

	*/
	Tile * Floor::tile(int i, int j)
	{
		return tiles[i][j];
	};

	vector<Tile*>& operator[] (unsigned i)
	{
		return tiles[i];
	}

	/**

	*/
	void setTile(int i, int j, tileType t)
	{
		tiles[i][j] = new Tile(i,j,t);
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
		
	}

	int getNumber()
	{
		return floorNumber;
	}

	void setWall()
	{

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
				cout << tiles[i][j]->getType() << " ";
			cout << endl;
		}
	}

private:
	vector<vector<Tile*>> tiles;
	int floorNumber;
	//Guard guard;
	//GuardDeck guardDeck;
	vector<Coord> alarmTokens;
	Coord stairToken;
};