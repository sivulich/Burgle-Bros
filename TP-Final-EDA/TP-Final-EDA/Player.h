#pragma once
#include "Configs.h"
#include "actionNode.h"
#include "Loot.h"
#include "Tile.h"

class Player
{
public:
	/**
	
	*/
	Player(){};

	/**

	*/
	Player(string & playerName);

	/**
		Sets the ID of the player
	*/
	void setName(string & playerName);

	/**

	*/
	void setId(characterID character);
	
	/**
		Reset the player action tokens
	*/
	void newTurn();
	
	/**
		Sets the player position to the parameter given
	*/
	void move(Coord & newPos);
	
	/**
	Appends the action given to the front of the list of player actions.
	*/
	void newAction(string & action);
	
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

	//vector<> visibleFrom;

	/**
		Appends the action given to the front of the list of player actions.
	*/
	list <actionNode> actions;
	list <Loot *> loots;
private:
	string name;
	characterID id;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	
};