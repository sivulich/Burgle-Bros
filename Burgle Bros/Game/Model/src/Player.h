#pragma once
#include "./Configs.h"
#include "../src/actionNode.h"
#include "../src/Loots/Loot.h"
#include <Tile.h>
#include "../src/Characters/Character.h"
#include "../src/PlayerInterface.h"
#include "./Board.h"
#include "./BaseModel.h"

class Player : public PlayerInterface, public BaseModel
{
public:
	//	Construct a player
	Player(Board * b, Player * p, int n);

	//	Hay que destruir el caracter... algo mas?
	~Player() {};

	// SETTERS
	//	Sets the name of the player
	void setName(string & playerName);

	//	Set player position to a coord, only moves player to this position and turn up the tile
	virtual void setPosition(Coord c)override;

	//	Sets the character the player will use
	void setCharacter(characterType type);
	void setCharacter(string type);

	//	Add the amount of action tokens you want
	void setActionTokens(int i) { actionTokens = i; };

	//	Add the amount of stealth tokens you want
	void setStealthTokens(int i) { stealthTokens = i; };

	// GETTERS

	//	Get player name
	virtual string getName()override;

	// Number of player (1 or 2)
	int getNumber() { return n; };

	//	Returns the player's positions
	virtual Coord getPosition()override;

	//	Return a vector of strings with the actions the player can do
	vector<string> getActions();

	// Get character type
	characterType getCharacter();

	// Get character type
	bool hasCharacter() { return character != nullptr; };

	//	Returns the amount of stealth tokens
	virtual int getStealthTokens()override;

	//	Returns the amount of action tokens
	virtual int getActionTokens()override;

	// Returns the vector with the coordinates the player is visible from
	virtual vector <Coord> getVisibleFrom()override;

	// Get the loots the player carries
	vector<Loot*>& getLoots() { return loots; };

	// Get the turn number
	int getTurn() { return turn; };


	// MISC

	//	Print player in console;
	void print();

	//	Return true if the player is on the roof of the building 
	bool isOnRoof();

	//
	//bool needConfirmationToMove(Coord c);

	//	Removes one stealth token if possible
	virtual void removeStealthToken()override;

	//	Removes one action token if possible
	virtual void removeActionToken()override;

	// 
	void addTurn() { turn++; };

	//	Reset the player action tokens
	virtual void resetActionTokens()override;

	// Return the coordinates where the player can move
	vector<Coord> whereCanIMove();

	// Return the coordinates where the player can peek
	vector<Coord> whereCanIPeek();

	//	Move the player to the tile
	bool move(Coord c);

	//	Peek the tile
	bool peek(Coord c);

	//	Use a token from a Computer Room or
	void useToken();

	//	Add a token to a Computer Room
	void addToken();

	//	Add a die to a Safe
	void addDice();

	//	Simulates a die being thrown
	virtual  int throwDice();

	//
	virtual void addLoot(lootType l)override;

	// Return true if the player has the specified loot
	virtual bool has(lootType l)override;

	// Returns true if the player has at least one loot.
	virtual bool hasLoot()override;

	//	Retrun true if the guard can see the player from that position
	virtual bool isVisibleFrom(Coord c)override;

	//	Set a vector of tiles from where the guard can see the player 
	void setVisibleFrom(vector<Coord> v) { if (!v.empty()) this->visibleFrom = v; };

	//	Clears the visibleFrom list
	virtual void clearVisibleFrom() override;

	//	Adds a coordinate to the list of coordinates the player is visible from
	virtual void addVisibleTile(Coord tile)override;



	// REVISAR DE ACA PA BAJO

	//	Creates an alarm in the specified coord (if player is ________)
	bool createAlarm(Coord c);

	//	Place a crow token in the specified coord (if player is ________)
	void placeCrow(Coord c);

	//  Appends a new action to the action history
	virtual void newAction(string action, Coord tile)override;


	/////////// ??????????????? :O FUNCIONES WHAT THE ACTUAL FAK
	/**
		Tells the tile the player wants to add a token
	*/
	void wantsToAddToken() { currentTile->doAction(toString(ADD_TOKEN), this); };

	/**
		Tells the tile the player wants use an action to throw the dice
	*/
	void wantsToThrowDice() { currentTile->doAction(toString(THROW_DICE), this); };

	/**
		Tells the tile the player wants use a token
	*/
	void wantsToUseToken() { currentTile->doAction(toString(USE_TOKEN), this); };

	/**

	*/
	void useAbility(bool b) { character->useAbility(b); };
	//////////////////////////////////////////

private:
	// Name of the player
	string name;
	// Number of player
	int n;
	// Character the player is using
	Character * character;
	// Tile where character token is placed on the board
	Tile * currentTile;
	// Pointer to other player (needed to know position of other player, to offer or request loot)
	Player * otherPlayer;
	// Pointer to the board, to have access to tiles
	Board * board;
	// Number of action tokens
	int actionTokens;
	// Number of stealth tokens
	int stealthTokens;
	// Number of turns the player has played
	int turn;
	// History of actions
	vector<actionNode> actions;
	// Loots the player carries 
	vector <Loot*> loots;
	// Coords from where the guard can see the player (only player current position normally, unless special cases)
	vector <Coord> visibleFrom;
	// Vector containing strings with possible actions player can do at the moment
	vector <string> possibleActions;
	// ???
	vector <unsigned int> dice;
	
	
	//       PRIVATE METHOD
	//	Move to a tile
	bool move(Tile * newTile);
	//	Peek a tile
	bool peek(Tile * newTile);
	//	Sets the player's position with a tile pointer
	void setPosition(Tile*  newTile);
};