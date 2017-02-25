#pragma once

class PlayerInterface
{
public:
	PlayerInterface();
	~PlayerInterface();

	/**
		Get player name
	*/
	virtual string getName() = 0;

	/**
		Returns the player's positions
	*/
	virtual Coord getPosition() = 0;

	/**

	*/
	virtual characterType getCharacterType() = 0;

	/**
		Reset the player action tokens
	*/
	virtual void resetActionTokens() = 0;

	/**
		Removes 1 stealth token if possible
	*/
	virtual void removeStealthToken() = 0;

	/**
		Removes 1 action token if possible
	*/
	virtual void removeActionToken() = 0;
	/**
		Returns the amount of stealth tokens
	*/
	virtual int getStealthTokens() = 0;

	/**
		Returns the amount of action tokens
	*/
	virtual int getActionTokens() = 0;

	/**
		Simulates a die being thrown
	*/
	virtual int throwDice() = 0;

	/**
		Returns true if the player has at least one loot.
	*/
	virtual bool hasLoot() = 0;


	/**
		Adds a coordinate to the list of coordinates the player is visible from
	*/
	virtual void addVisibleTile(Coord tile) = 0;

	/**
		Returns the vector with the coordinates the player is visible from
	*/
	virtual vector <Coord>& getVisibleFrom() = 0;

	/**

	*/
	virtual void setVisibleFrom(vector <Coord> newCoords) = 0;

	/**

	*/
	virtual void changePos(Coord newPos) = 0;

};

