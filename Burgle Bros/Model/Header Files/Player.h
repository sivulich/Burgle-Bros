#pragma once
#include "./Configs.h"
#include "./actionNode.h"

#include "./Loots/Loot.h"
#include "./Tiles/Tile.h"
#include "./Characters/Character.h"

class Player
{
public:
	/**
	
	*/
	Player(){};
	~Player() {};

	/**

	*/
	Player(string & playerName);

	/**
		Sets the name of the player
	*/
	void setName(string & playerName);

	/**
		Returns the player's positions
	*/
	Coord getPosition();

	/**

	*/
	void setCharacter(characterType type);
	
	/**
		Reset the player action tokens
	*/
	void resetActionTokens();
	
	/**
		Checks adjacency and tries to move to the tile, returns true if successful
		@params newPos pointer to the tile the player wants to move to
	*/
	bool move(Tile * newTile);

	/**
		Peek the tile in exchange of an action token
	*/
	bool peek(Tile * newTile);
	
	/**
		Appends a new action to the action history
		@params action the string of the action that occured
		@params tile coordinate to the tile where the action happened
	*/
	void newAction(string action, Coord tile);
	
	/**
		Removes 1 stealth token if possible
	*/
	void removeStealthToken();
	
	/**
		Removes 1 action token if possible
	*/
	void removeActionToken();
	/**
		Returns the amount of stealth tokens
	*/
	int getStealthTokens();

	/**
		Returns the amount of action tokens
	*/
	int getActionTokens();

	/**
		Simulates a die being thrown
	*/
	int throwDice();

	/**
	
	*/
	void addLoot(Loot * l);

	/**
		Returns true if the player has at least one loot.
	*/
	bool hasLoot();

	/**
		Clears the coordinates from where the player is visible from
	*/
	void clearVisibleFrom();

	/**
		Adds a coordinate to the list of coordinates the player is visible from
	*/
	void addVisibleTile(Coord tile);

	/**
		Returns the vector with the coordinates the player is visible from
	*/
	vector <Coord>& getVisibleFrom();

	/**
	
	*/
	void setVisibleFrom(vector <Coord> newCoords);

	/**
	Get player name
	*/
	string getName();

	/**
	
	*/
	characterType getCharacterType();

	/**
	
	*/
	void changePos(Coord newPos) { pos = newPos; };

private:
	string name;
	Character * character;
	Tile * currentTile;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	list <actionNode> actions;
	vector <Loot*> loots;
	vector <Coord> visibleFrom;
	vector <unsigned int> dice;	//holds the value of the dice thrown in the players turn (from 1 to 6) up to four dice
									// POR QUE UN VECTOR???
										// porque para el keypad necesito tirar el dado muchas veces sin salir de la tile, y es para que quede un registro de lo que salio
};