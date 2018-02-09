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

	// Get player current Destination
	void setDest(Coord c) { if (c.row < F_HEIGHT && c.col < F_WIDTH && c.floor < NUMBER_FLOORS || c==ROOF) destination = c; else destination = NPOS; };

	// GETTERS

	//	Get player name
	virtual string getName()override;

	// Number of player (1 or 2)
	virtual int getNumber() { return n; };

	//	Returns the player's positions
	virtual Coord getPosition()override;

	//	Return a vector of strings with the actions the player can do
	vector<string> getActions();

	// Return a vector of strings with the actions the player can do and notifies view about it
	vector < string> Player::gettActions();

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

	// Get player current Destination
	Coord getDest() { return destination; };

	Tile * getCurrentTile() { return currentTile; };


	// MISC

	//	Print player in console;
	void print();

	//	Return true if the player is on the roof of the building 
	bool isOnRoof();

	// Set if player is playing or not
	bool isPlaying() { return playing; };
	void isPlaying(bool b) { playing = b; notify(); };

	virtual bool isThrowingDices() { return throwingDices; };

	virtual void dicesLeft2Throw(bool b) { throwingDices = b; };
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

	// Returns player adjacent coordinates (not through walls)
	vector<Coord> getAdjacentJuicer();

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
	virtual  bool throwDice(int n);
	// Return a number between 1 and 6
	int throwDice();

	//
	virtual int getDice() { return currDice; };
	//
	virtual void addLoot(lootType l)override;

	//	Return true if the player has the specified loot
	virtual bool has(lootType l)override;

	//	Returns true if the player has at least one loot.
	virtual bool hasLoot()override;

	//
	void setLocal(bool b) { local = b; };
	bool isLocal() { return local; };
	//
	int getLoot2bTraded() { return loot2bTransfered; };

	//
	void setLoot2bTraded(int n) { loot2bTransfered = n; };

	//
	void giveLoot( int n);

	//
	void receiveLoot(int n);

	//
	virtual void pickUpLoot(lootType l);

	//
	virtual void removeLoot(Loot * l) { if (l != nullptr) loots.erase(remove(loots.begin(), loots.end(), l), loots.end()); notify(); }

	//
	bool losePersianKitty();

	//
	void areLootsReady();

	//	Retrun true if the guard can see the player from that position
	virtual bool isVisibleFrom(Coord c)override;

	//	Set a vector of tiles from where the guard can see the player 
	void setVisibleFrom(vector<Coord> v) { if (!v.empty()) this->visibleFrom = v; };

	//	Clears the visibleFrom list
	virtual void clearVisibleFrom() override;

	//	Adds a coordinate to the list of coordinates the player is visible from
	virtual void addVisibleTile(Coord tile)override;

	//	Returns true if user is required to confirm movement or action
	confirmation Player::needConfirmation(Coord c);

	//	Returns true if user is required to confirm movement
	confirmation Player::needConfirmationToMove(Coord c);

	// REVISAR DE ACA PA BAJO

	//	Creates an alarm in the specified coord (if player is ________)
	bool createAlarm(Coord c);

	//	Place a crow token in the specified coord (if player is ________)
	bool placeCrow(Coord c);

	//  Appends a new action to the action history
	virtual void newAction(string action, Coord tile, int dice)override;

	// Tells the tile the player wants to spend to enter
	void spentOK() { currentTile->doAction(toString(SPENT_OK), this); };

	/**
	 Receives true if ability was used, not to be used again in the turn. To make ability available again receive false.
	*/
	void useAbility(bool b) { if (b==true) character->spendAbility(); else character->restoreAbility(); notify(); };
	//////////////////////////////////////////

	/**
	
	*/
	bool canIUseAbility() { return this->character->canUseAbility(); };

private:
	// Name of the player
	string name;
	// Number of player
	int n;
	// If its player turn playing=true
	bool playing;
	//
	bool local;
	//
	Coord lastPos, destination;
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
	// Crow Token position if there is any
	Coord crowToken;
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
	//
	int currDice;
	//
	bool throwingDices;
	//
	int loot2bTransfered;


	//       PRIVATE METHOD
	//	Move to a tile
	bool move(Tile * newTile);
	//	Peek a tile
	bool peek(Tile * newTile);
	//	Sets the player's position with a tile pointer
	void setPosition(Tile*  newTile);
};