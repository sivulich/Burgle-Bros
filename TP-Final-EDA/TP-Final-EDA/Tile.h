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
	Tile(int x, int y);
	
	/**
		Peek the tile (Remove action, flip tile)
	*/
	virtual void peek(Player p);
	/**
		Checks if player has action token and tile is down
	*/
	virtual bool canPeek(Player p);

	/**
		Moves the player to the tile
	*/
	virtual void moveTo(Player p);

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
	void setCoord(int x, int y);

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
		Activate an alarm in the tile.
	*/
	void  setAlarm(bool b);

	/**
		Returns a vector of strings with the REGULAR actions the player can do (MOVE and PEEK only)
	*/
	virtual vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos) = 0;

	/**
		Applies the action given to the player (MOVE and PEEK only)
	*/
	virtual void doAction(string action, Player p);

	/**
		If flipped returns the safe number, else returns 0.
	*/
	int getSafeNumber();

	/**

	*/
	vector<Tile*>& getAdjacent();

	/**
		Returns the floor number
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

	/**
		Returns true if the tile given is adjacent
	*/
	bool isAdjacent(Coord t);

	/**
		Adds the surrounding tile's coordinates to the player visible from
	*/
	void updateVisibleFrom(Player p);

	/**
		Commits an action to the player list of actions
	*/
	void addPlayerAction(Player p, string action);
	

	bool walls[4];

protected:
	Coord coord;
	int floor;
	bool alarm;
	int safeNumber;
	int floor;
	tileType type;
	vector<Coord> adjacent;
	vector<string> actions;
};
