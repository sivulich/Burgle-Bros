#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
#include "../Loots/LootFactory.h"
/*
Safes are the goal. Roll the combination to open them. When opened, draw a Loot, and increase the Guard's 
movement die by one on this floor and all those below it.
*/

//	CUANDO SALGA DE LA SAFE TILE, EL MODELO DEBE CHECKEAR EN LAS TILES (que esten boca arriba) DE LA FILA Y LA COLUMNA. 
//	SI EL NUMERO DE LA TILE NO APARECE EN LA COMBINATION, ES PORQUE ESTA "CRACKED"


class Safe : public Tile
{
public:
	Safe(int floor, int col, int row) : Tile(SAFE,floor, col, row) { tokens = 0; safeCracked = false; };
	~Safe();

	void setLoot(lootType l)
	{
		loot.push_back(LootFactory().newLoot(l));
	}
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
	virtual void doAction(string action, PlayerInterface * player) override;

	/**
		Adds a tile to the combination of tiles needed to crack the safe.
		@params t the tile added to the safe combination.
	*/
	void addCrackTile( Tile * t) { combinationTiles.push_back(t); };


private:
	unsigned int tokens;
	vector <Tile *> combinationTiles;
	bool safeCracked;

	bool safeIsOpen() { return safeCracked; };
	void addToken() { if(tokens<6)	tokens++; };
	void removeToken() { if(tokens>0)	tokens--; };
	unsigned int getTokens() { return tokens; };

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

