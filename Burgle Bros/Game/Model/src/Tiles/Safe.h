#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
#include "../Loots/LootFactory.h"
/*
Safes are the goal. Roll the combination to open them. When opened, draw a Loot, and increase the Guard's 
movement die by one on this floor and all those below it.
*/

class Safe : public Tile
{
public:
	Safe(int floor, int col, int row) : Tile(SAFE, floor, col, row) { currentPlayer = -1; currentTurn = -1; dices = 0; dicesThisTurn = 0; safeCracked = false; keyCardHere = true; this->alarmTile = false; };
	~Safe();

	void enter(PlayerInterface * player);

	void Safe::exit(PlayerInterface * player);

	void setLoot(lootType l) { safeLoot = l; };
	lootType getLoot() { return safeLoot; };
	void giveLootToPlayer(PlayerInterface * player);
	/**
		Returns a vector of strings with the actions the player can do on the tile they are on
		@param p Player who wants to check the actions
	*/
	virtual vector<string> getActions(PlayerInterface * player) override;

	/**
		Applies the action given to the player
		@param action Action to execute
		@param p Player who wants to do the action
	*/
	virtual bool doAction(string action, PlayerInterface * player) override;

	/**
		Adds a tile to the combination of tiles needed to crack the safe.
		@params t the tile added to the safe combination.
	*/
	void addCrackTile( Tile * t) { combinationTiles.push_back(t); };

	/* Add a dice to later roll and crack the safe*/
	void addDice() { if (dices < 6)dices++; notify(); };

	void addSafe(Tile * safe) { otherSafes.push_back(safe); };

	void isKeyCardHere(bool b) { keyCardHere = b; };

	unsigned int getTokens() { return dices; };

	bool safeIsOpen() { return safeCracked; };
private:
	lootType safeLoot;
	unsigned int dices;
	unsigned int dicesThisTurn;
	int currentPlayer, currentTurn;
	vector <Tile *> combinationTiles;
	bool safeCracked;
	bool keyCardHere;

	vector<Tile *> otherSafes;
	
	void removeToken() { if(dices>0)	dices--; };

	/**
		Checks if the number given is one of the combination numbers. If so, removes that number from the list and returns the amount of
		numbers removed from the vector.
		@params number you want to try 
	*/
	void trySafeNumber(int number);

	/**
	Returns true if the tile given can be cracked
	*/	
	bool Safe::canCrack( Tile * t, int dice);


};

