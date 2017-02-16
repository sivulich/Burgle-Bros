#pragma once
#include "Player.h"
#include "Configs.h"

typedef enum {
	ATRIUM = 0x01,
	CAMERA,
	COMPUTER_ROOM_F,
	COMPUTER_ROOM_L, COMPUTER_ROOM_M, DEADBOLT, FINGERPRINT, FOYER, KEYPAD, LABORATORY, LASER, LAVATORY, MOTION, SAFE, SCANNER, SECRET_DOOR, SERVICE_DUCT, STAIR, THERMO, WALKWAY
} tileType;


class Tile
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
	int getType();

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
	vector<string>& getActions(Player p);

	/**

	*/
	bool doAction(string Action, Player p);

	/**

	*/
	int getSafeNumber();

	/**

	*/
	vector<Tile*>& getAdjacent();

private:
	bool flipped;
	bool alarm;
	int safeNumber;
	int type;
	vector<string> actions;
	vector<Tile*> adjacent;
	Coord coord;
};
