#pragma once
#include "../src/BaseCard.h"
#include <Enumerations.h>
#include <Configs.h>
#include <BaseModel.h>
#include "../src/PlayerInterface.h"
#include "../src/Loots/Loot.h"


class Tile : public BaseCard
{
public:
	//	Default constructor.
	Tile();

	//	Construct a tile with a position in the floor and a tileType.
	Tile(tileType t, unsigned floor, unsigned col, unsigned row);

	//	Apart from turning up the card, sort the safe number
	virtual void turnUp();

	//	Peek the tile
	void peek();

	//	Return true if the player can move to the tile, checking adjacency. On child classes check specific conditions.
	virtual bool canMove(PlayerInterface * player);

	//	Executes the tile's special actions, if any...
	virtual void enter(PlayerInterface * player);

	//	Executes any special action when leaving the tile
	virtual void exit(PlayerInterface * player) {};

	//	Returns the position of the tile in the floor.
	Coord getPos();

	// Return the floor number
	int floor();

	// Return the column number
	int col();

	// Return the row number
	int row();

	//	Returns the type of the tile.
	tileType getType();

	//	Return true if the tile is from the given type
	bool is(tileType t);

	//	Activate an alarm in the tile.
	void setAlarm(bool b);

	//	Checks if there is an alarm activated in the tile.
	bool hasAlarm();

	// 
	void setLoot(Loot * l);

	//
	void removeLoot(Loot * loot2Remove) { if (!loot.empty())	loot.erase(remove(loot.begin(), loot.end(), loot2Remove), loot.end()); };

	//	Checks if there is a loot on tile.
	bool hasLoot();

	//
	vector<Loot *> getLoot() { return loot; }

	//	Returns a vector of strings with the actions the player can do on the tile they are on.
	//	Actions PEEK and MOVE are always valid. On each tileType overload the function
	virtual vector<string> getActions(PlayerInterface * player);

	// Clears visible from and adds the current tile to visibleFrom
	virtual void updateVisibleFrom(PlayerInterface * player);

	//	Applies the action given to the player
	virtual bool doAction(string action, PlayerInterface * player);

	//	If tile is flipped returns the safe number, else returns 0.
	int getSafeNumber();

	//	Return a vector of Coords where player can move (override special cases)
	virtual vector<Coord> whereCanIMove();

	//	Return a vector of Coords where player can Peek (override special cases)
	virtual vector<Coord> whereCanIPeek();

	//	Return adjacent coordinates
	vector<Coord> getAdjacent();

	//	Add a coord to the adjacent list
	void addAdjacent(Coord c);

	//	Delete a coord from the adjacent list
	void deleteAdjacent(Coord b);

	//	Returns true if the tile given is adjacent
	bool isAdjacent(Coord t);

	//	Check for walls	
	bool hasEastWall() { return eastWall; };
	bool hasWestWall() { return westWall; };
	bool hasNorthWall() { return northWall; };
	bool hasSouthWall() { return southWall; };

	void setNorthWall(bool b) { northWall = b; }
	void setEastWall(bool b) { eastWall = b; }
	void setWestWall(bool b) { westWall = b; }
	void setSouthWall(bool b) { southWall = b; }

	void crackTile() { crackToken = true; notify(); };
	bool hasCrackToken() { return crackToken; };

	void setStairToken(bool b) { stairToken = b; notify(); };
	bool hasStairToken() { return stairToken; };

	void setCrowToken(bool b) { crowToken = b; notify(); };
	bool hasCrowToken() { return crowToken; };

	
	//Returns the amount of hack tokens in the tile
	int getHackTokens() { return hackToken; };

	//	Returns true if you could hide from the guard. Used for Lavatory.
	virtual bool tryToHide() { return false; };

	void guardIs(bool b) { hasGuard = b; };

	bool guardHere() { return hasGuard; };

protected:
	// Coord containing floor, column and row of the tile
	Coord coord;
	// Type of tile
	tileType type;
	// Number to crack the safe
	int safeNumber;
	// Vector with adjacent tiles (coords)
	vector<Coord> adjacent;
	// A tile can have a loot (If it's a SAFE tile or a loot has been dropped)
	vector<Loot*> loot;
	// Tokens
	bool crackToken, crowToken, stairToken, alarmToken, hackerHere, hasGuard, northWall, southWall, eastWall, westWall;
	//
	int hackToken;
	//
	bool alarmTile;
};
