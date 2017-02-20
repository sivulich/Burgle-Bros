#pragma once
#include "Player.h"
#include "Configs.h"
#include "TileCard.h"

class
	Tile
{
public:
	Tile();
	Tile(int x, int y, tileType type);
	
	/**

	*/
	virtual void peek(Player p);

	/**

	*/
	virtual bool moveTo(Player p);

	/**

	*/
	Coord getCoord() { return coord; };
	/**

	*/
	tileType getType();

	/**

	*/
	bool hasAlarm();

	/**

	*/
	bool isFlipped();

	/**

	*/
	void  setAlarm(bool b);

	/**
	*/
	void setCoord(int x, int y);
	/**

	*/
	vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);

	/**

	*/
	bool doAction(string Action, Player p);

	/**

	*/
	int getSafeNumber();

	/**

	*/
	vector<Tile*>& getAdjacent();

	/**
	*/
	int getFloor() { return floor; };
private:
	bool flipped;
	bool alarm;
	int safeNumber;
	TileCard tileCard;
	vector<Tile*> adjacent;
	Coord coord;
	int floor;
};
