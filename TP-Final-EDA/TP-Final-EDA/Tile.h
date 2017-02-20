#pragma once
#include "Player.h"
#include "BaseCard.h"
#include "Enumerations.h"

DEFINE_ENUM_WITH_CONVERSIONS(tileType,
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
		//ESTO QUE LO HAGA LA CARTA O EL PLAYER??
	*/
	virtual void peek(Player p); //=0!!!

	/**
		//ESTO QUE LO HAGA LA CARTA O EL PLAYER??
	*/
	virtual bool moveTo(Player p); //=0!!!

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
	Coord coord;
	int floor;
	bool alarm;
	int safeNumber;
	tileType type;
	vector<Tile*> adjacent;	
};
