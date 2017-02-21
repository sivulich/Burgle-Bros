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
		Sets the name of the player
	*/
	void setName(string & playerName);
	/**
		Returns the player's positions
	*/
	Coord getPosition() { return pos; };
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

	//vector<> visibleFrom;

	/**
		Clears the coordinates from where the player is visible from
	*/
	void clearVisibleFrom() { visibleFrom.clear(); };
	/**
		Adds a coordinate to the list of coordinates the player is visible from
	*/
	void addVisibleTile(Coord tile) { visibleFrom.push_back(tile); };
	/**
		Returns the vector with the coordinates the player is visible from
	*/
	vector <Coord>& getVisibleFrom() { return visibleFrom; };


private:
	string name;
	characterID id;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	list <actionNode> actions;
	list <Loot> loots;
	vector <Coord> visibleFrom;
	
};