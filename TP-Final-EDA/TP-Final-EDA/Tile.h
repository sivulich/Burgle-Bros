#pragma once
#include "Player.h"
#include "BaseCard.h"
#include "Enumerations.h"

DEFINE_ENUM_WITH_CONVERSIONS (tileType,
(ATRIUM, 0x01)
(CAMERA, 0x02)
(COMPUTER_ROOM_F, 0x03)
(COMPUTER_ROOM_L, 0x04)
(COMPUTER_ROOM_M, 0x05)
(DEADBOLT, 0x06)
(FINGERPRINT, 0x07)
(FOYER, 0x08)
(KEYPAD, 0x09)
(LABORATORY, 0x0A)
(LASER, 0x0B)
(LAVATORY, 0x0C)
(MOTION, 0x0D)
(SAFE, 0x0E)
(SCANNER, 0x0F)
(SECRET_DOOR, 0x10)
(SERVICE_DUCT, 0x11)
(STAIR, 0x12)
(THERMO, 0x13)
(WALKWAY, 0x14))


/**
	Pure abstract class of a tile.
*/
class Tile : public BaseCard
{
public:
	/**
		Default constructor.
	*/
	Tile();

	/**
		Construct a tile with a position in the floor and a tileType.
	*/
	Tile(unsigned floor, unsigned col, unsigned row);
	
	/**
		Peek the tile (Remove action, flip tile)
		Apart from turning up the card, sort the safe number
	*/
	virtual void peek(Player p);
	/**
		Checks if player has action token and tile is down
	*/
	virtual bool canPeek(Player p);

	virtual void turnUp()override;

	/**
		Moves the player to the current tile
	*/
	virtual void enterTile(Player p);

	/**
		True if the player has an action token
	*/
	virtual bool canMove(Player p);

	/**
		Returns the position of the tile in the floor.
	*/
	Coord getPos() { return coord; };

	/**
		Set the position of the tile in the floor.
	*/
	void setCoord(unsigned floor, unsigned col,unsigned row);

	/**
		Returns the type of the tile.
	*/
	tileType getType();

	/**
		Checks if there is an alarm activated in the tile.
	*/
	bool hasAlarm();

	/**
		Activate an alarm in the tile.
	*/
	void setAlarm(bool b);

	/**
		Returns a vector of strings with the REGULAR actions the player can do (MOVE and PEEK only)
	*/
	virtual vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);

	/**
		Applies the action given to the player (MOVE and PEEK only)
	*/
	virtual void doAction(string action, Player p, Coord guardPos, Coord partnerPos);

	/**
		If flipped returns the safe number, else returns 0.
	*/
	int getSafeNumber();

	/**
		Return a vector of Coords of adjacent tiles
	*/
	vector<Coord>& getAdjacent();

	/**
		Return the floor number
	*/
	int floor() { return coord.floor; };

	/**
		Return the col number
	*/
	int col() { return coord.col; };

	/**
		Return the row number
	*/
	int row() { return coord.row; };

	/**
		Add a coord to the adjacent list
	*/
	void setAdjacent(Coord c);

	/**
		Delete a coord from the adjacent list
	*/
	void deleteAdjacent(Coord b);
	
	/**
		Returns true if the tile given is adjacent
	*/
	bool isAdjacent(Coord t)
	{
		return find(adjacent.begin(), adjacent.end(), t) != adjacent.end();
	}
	
	/**
		Return true if the tile is from the given type
	*/
	bool is(tileType t)
	{
		return t == getType();
	}

	/**
		Adds the surrounding tile's coordinates to the player visible from
	*/
	void updateVisibleFrom(Player p);

	/**
		Commits an action to the player list of actions
	*/
	void addPlayerAction(Player p, string action);
	
protected:
	Coord coord;
	tileType type;
	bool alarm;
	int safeNumber;
	vector<Coord> adjacent;
	vector<string> actions;
};
