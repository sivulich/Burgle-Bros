#pragma once

#include "../Header Files/Configs.h"
class PlayerInterface
{
public:
	PlayerInterface() {};
	~PlayerInterface() {};

	/**
		Get player name
	*/
	virtual string getName() = 0;

	/**
		Returns the player's positions
	*/
	virtual Coord getPosition() = 0;

	/**
		Sets the player position
	*/
	virtual void setPosition(Coord c) = 0;
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
		Returns true if the player has at least one loot.
	*/
	virtual bool hasLoot() = 0;

	/**
		Returns true if the player has this loot type
	*/
	virtual bool has(lootType l)=0;

	/**
		Retrun true if the guard can see the player from that position
	*/
	virtual bool isVisibleFrom(Coord c)=0;

	/**
		Adds a coordinate to the list of coordinates the player is visible from
	*/
	virtual void addVisibleTile(Coord tile) = 0;

	/**
		Returns the vector with the coordinates the player is visible from
	*/
	virtual vector <Coord> getVisibleFrom() = 0;

	/**
		Clears the visibleFrom list
	*/
	virtual void clearVisibleFrom() =0;

	/**
		Simulates a die being thrown
	*/
	virtual int throwDice() = 0;

	/**
	Appends a new action to the action history
	@params action the string of the action that occured
	@params tile coordinate to the tile where the action happened
	*/
	virtual void newAction(string action, Coord tile)=0;

};

