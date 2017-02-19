#pragma once
#include "Configs.h"
#include "Tile.h"
//#include "Guard.h"
//#include "GuardDeck.h"

class Floor
{
public:
	/**
		Default constructor
	*/
	Floor() : tiles(4,vector<Tile*>(4,nullptr)) {};

	/**
		Construct floor with floor number
	*/
	Floor(int n) : floorNumber(n), tiles(4, vector<Tile*>(4, nullptr))
	{
		
	};

	/**
		Acces a tile in coord (COL,ROW)
	*/
	Tile * Floor::tile(int i, int j)
	{
		return tiles[i][j];
	};

	/**
		
	*/
	vector<Tile*>& operator[] (unsigned i)
	{
		return tiles[i];
	}

	/**
		Set a specific tile of type t in coord (COL,ROW) 
	*/
	void setTile(int i, int j, tileType t)
	{
		tiles[i][j] = new Tile(i,j,t);

		if (i > 0 && tiles[i - 1][j] != nullptr)
		{
			tiles[i][j]->setAdjacent(tiles[i - 1][j]);
			tiles[i - 1][j]->setAdjacent(tiles[i][j]);
		}
		if (i < 3 && tiles[i + 1][j] != nullptr)
		{
			tiles[i][j]->setAdjacent(tiles[i + 1][j]);
			tiles[i - 1][j]->setAdjacent(tiles[i][j]);
		}
		if (j > 0 && tiles[i][j - 1] != nullptr)
		{
			tiles[i][j]->setAdjacent(tiles[i][j - 1]);
			tiles[i][j - 1]->setAdjacent(tiles[i][j]);
		}
		if (j < 3 && tiles[i][j + 1] != nullptr)
		{
			tiles[i][j]->setAdjacent(tiles[i][j + 1]);
			tiles[i][j + 1]->setAdjacent(tiles[i][j]);
		}
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

	/**

	*/
	int getNumber()
	{
		return floorNumber;
	}

	/**

	*/
	void setWall(Coord a, Coord b)
	{
		/*if (isAdjacent(a, b))
		{
			tiles[a.first][a.second]->deleteAdjacent(b);
			tiles[b.first][b.second]->deleteAdjacent(a);
		}*/
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
	}

private:
	vector<vector<Tile*>> tiles;
	int floorNumber;
	//Guard guard;
	//GuardDeck guardDeck;
	vector<Coord> alarmTokens;
	Coord stairToken;
};