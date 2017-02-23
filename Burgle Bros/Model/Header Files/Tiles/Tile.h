#pragma once
#include "../Player.h"
#include "../BaseCard.h"
#include "../Enumerations.h"
#include "../Configs.h"

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

		@param floor floor of the tile
		@param col column of the tile
		@param row row of the tile
	*/
	Tile(unsigned floor, unsigned col, unsigned row);
	
	/**
		Peek the tile 
		@param p player who is peeking
	*/
	virtual void peek(Player p);

	/**
		Return true if the player can peek the tile
		@param p player who is peeking
	*/
	virtual bool canPeek(Player p);

	/**
		Moves the player to the tile
		@param p player who is moving

	*/
	virtual void enterTile(Player p);

	/**
		True if the player has an action token
	*/
	virtual void moveTo(Player p);

	/**
		Return true if the player can move to the tile
		@param p player who is moving
	*/
	virtual bool canMove(Player p);

	/**
		Apart from turning up the card, sort the safe number
	*/
	virtual void turnUp()override;

	/**
		Returns the position of the tile in the floor.
	*/
	Coord getPos();

	/**
		Set the position of the tile in the floor.
		
		@param floor floor of the tile
		@param col column of the tile
		@param row row of the tile
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
		@param p Player who wants to check the actions
		@param guardPos position of the guard int the board
		@partnerPos position of the other player in the board
	*/
	virtual vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);

	/**
		Applies the action given to the player (MOVE and PEEK only)
		@param action Action to execute
		@param p Player who wants to do the action
	*/
	virtual void doAction(string action, Player p, Coord guardPos, Coord partnerPos);

	/**
		If tile is flipped returns the safe number, else returns 0.
	*/
	int getSafeNumber();

	/**
		Return a vector of Coords of adjacent tiles
	*/
	vector<Coord>& getAdjacent();

	/**
		Return the floor number
	*/
	int floor();

	/**
		Return the column number
	*/
	int col();

	/**
		Return the row number
	*/
	int row();

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
	bool isAdjacent(Coord t);
	
	/**
		Return true if the tile is from the given type
	*/
	bool is(tileType t);

	/**
		Adds the adjacent tile's coordinates to the player visible from list
	*/
	void updateVisibleFrom(Player p);

	// CONSIDERAR PONER ESTA FUNCION PROTECTED; PORQUE NO SE VA A USAR DESDE AFUERA DE UN TILE O SI?
	/**
		Adds an action node to the player
		@param p player to add an action
		@param action action to be added
	*/
	void addPlayerAction(Player p, string action);
	
protected:
	// Coord containing floor, column and row of the tile
	Coord coord;
	// Type of tile
	tileType type;
	// If an alarm is ringing in the tile alarm=true
	bool alarm;
	// Number to crack the safe
	int safeNumber;
	// Vector with adjacent tiles (coords)
	vector<Coord> adjacent;
	// ESTO NO SE COMO COMENTARLO
	vector<string> actions;
};
