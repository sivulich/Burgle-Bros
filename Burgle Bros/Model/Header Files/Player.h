#pragma once
#include "./Configs.h"
#include "./actionNode.h"

#include "./Loots/Loot.h"
//#include "./Tiles/Tile.h"
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
	void resetStealthTokens();
	
	/**
		Sets the player position to the parameter given
	*/
	void move(Coord newPos);
	
	/**
		Appends the action given to the front of the list of player actions.
	*/
	void newAction(actionNode node);
	
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
	//vector<> visibleFrom;

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
	Get player name
	*/

	string getName();
	characterType getCharacterType();
private:
	string name;
	Character * character;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	list <actionNode> actions;
	vector <Loot*> loots;
	vector <Coord> visibleFrom;
	vector <unsigned int> dice;	//holds the value of the dice thrown in the players turn (from 1 to 6)
									// POR QUE UN VECTOR???
};