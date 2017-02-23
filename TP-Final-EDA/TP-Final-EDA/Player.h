#pragma once
#include "Configs.h"
#include "actionNode.h"
#include "Loot.h"
#include "Tile.h"
#include "Character.h"

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
	void setCharacter(characterType type);
	
	/**
		Reset the player action tokens
	*/
	void newTurn();
	
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
	void addLoot(Loot * l) { loots.push_back(l); };
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

	/**
	Get player name
	*/

	string getName() { return name; };
	characterType getCharacterType() { return character->getType(); };
private:
	string name;
	Character* character;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	list <actionNode> actions;
	vector <Loot*> loots;
	vector <Coord> visibleFrom;
	vector <unsigned int> dice;	//holds the value of the dice thrown in the players turn (from 1 to 6)
};