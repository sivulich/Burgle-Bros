#pragma once
#include "Player.h"
#include "Configs.h"
class Tile
{
public:
	/**
		Default constructor.
	*/
	Tile();

	/**
		Construct a tile with a position in the floor and a tileType.
	*/
	Tile(int x, int y, tileType type);
	
	/**
		//ESTO QUE LO HAGA LA CARTA O EL PLAYER??
	*/
	virtual void peek(Player p);

	/**
		//ESTO QUE LO HAGA LA CARTA O EL PLAYER??
	*/
	virtual bool moveTo(Player p);

	/**
		Returns the position of the tile in the floor.
	*/
	Coord getCoord() { return coord; };
	
	/**
		Returns the type of the tile.
	*/
	tileType getType();

	/**
		Checks if there is an alarm activated in the tile.
	*/
	bool hasAlarm();

	/**
		Flip the tile and sort the safe number.
	*/
	void flip();
	/**
		Checks if the tile is flipped.
	*/
	bool isFlipped();

	/**
		Activate an alarm in the tile.
	*/
	void  setAlarm(bool b);

	/**
		Set the position of the tile in the floor.
	*/
	void setCoord(int x, int y);
	
	/**
		
	*/
	vector<string>& getActions(Player p);

	/**

	*/
	bool doAction(string Action, Player p);

	/**
		If flipped returns the safe number, else returns 0.
	*/
	int getSafeNumber();

	/**

	*/
	vector<Tile*>& getAdjacent();

	/**
	*/
	int getFloor() { return floor; };

	void setAdjacent(Tile* t) { adjacent.push_back(t); };

	void deleteAdjacent(Coord b)
	{
		for (auto t : adjacent)
		{
			if (t->getCoord() == b);
				//adjacent.remove(t);
		}
	}

	bool walls[4];
private:
	bool flipped;
	bool alarm;
	int safeNumber;
	tileType type;
	vector<string> actions;
	vector<Tile*> adjacent;
	
	Coord coord;
	int floor;
};
