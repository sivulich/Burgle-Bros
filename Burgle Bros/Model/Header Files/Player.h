#pragma once
#include "./Configs.h"
#include "./actionNode.h"
#include "./Loots/Loot.h"
#include "./Tiles/Tile.h"
#include "./Characters/Character.h"
#include "./PlayerInterface.h"
#include "./Board.h"

class Player : public PlayerInterface
{
public:
	/**
	
	*/
	Player(Board * b);

	~Player() {};

	/**
		Sets the name of the player
	*/
	void setName(string & playerName);

	/**
		Returns the player's positions
	*/
	virtual Coord getPosition()override;

	/**
		Set player position with a coord
	*/
	virtual void setPosition(Coord c)override;

	/**
		Sets the player's position with a tile pointer
	*/
	void setPosition(Tile* c);
	
	/**
		Sets the character the player will use
	*/
	void setCharacter(characterType type);
	
	/**
		Reset the player action tokens
	*/
	virtual void resetActionTokens()override;
	
	/**
		Checks adjacency and tries to move to the tile, returns true if successful
		@params newTile pointer to the tile the player wants to move to
	*/
	bool move(Tile * newTile);

	/**
		Peek the tile in exchange of an action token
	*/
	void peek(Tile * newTile);
	
	/**
		Appends a new action to the action history
		@params action the string of the action that occured
		@params tile coordinate to the tile where the action happened
	*/
	virtual void newAction(string action, Coord tile)override;
	
	/**
		Removes 1 stealth token if possible
	*/
	virtual void removeStealthToken()override;
	
	/**
		Removes 1 action token if possible
	*/
	virtual void removeActionToken()override;
	/**
		Returns the amount of stealth tokens
	*/
	virtual int getStealthTokens()override;

	/**
		Returns the amount of action tokens
	*/
	virtual int getActionTokens()override;

	/**
		Simulates a die being thrown
	*/
	virtual  int throwDice()override;

	/**
	
	*/
	void addLoot(Loot * l);

	/**

	*/
	bool has(lootType l);
	/**
		Returns true if the player has at least one loot.
	*/
	virtual bool hasLoot()override;

	/**
		Retrun true if the guard can see the player from that position
	*/
	virtual bool isVisibleFrom(Coord c)override;

	/**
		Clears the coordinates from where the player is visible from
	*/
	void clearVisibleFrom();

	/**
		Adds a coordinate to the list of coordinates the player is visible from
	*/
	virtual void addVisibleTile(Coord tile)override;

	/**
		Returns the vector with the coordinates the player is visible from
	*/
	virtual vector <Coord>& getVisibleFrom()override;

	/**
	
	*/
	virtual void setVisibleFrom(vector <Coord> newCoords)override;

	/**
	Get player name
	*/
	virtual string getName()override;

	/**
	
	*/
	characterType getCharacterType();

	vector<Loot*>& getLoots() { return loots; };
private:
	string name;
	Character * character;
	Tile * currentTile;
	Board * board;
	int actionTokens;
	int stealthTokens;
	vector<actionNode> actions;
	vector <Loot*> loots;
	// Coord from where the guard can see the player
	// (player position normally, unless special cases)
	vector <Coord> visibleFrom;
	vector <unsigned int> dice;	//holds the value of the dice thrown in the players turn (from 1 to 6) up to four dice
									// POR QUE UN VECTOR???
										// porque para el keypad y el safe necesito tirar el dado muchas veces sin salir de la tile, y es para que quede un registro de lo que salio
											// AHhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh la re puta madre, porque no lo comentas???!!
};