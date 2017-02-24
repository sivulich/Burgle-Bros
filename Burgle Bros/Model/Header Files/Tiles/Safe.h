#pragma once
#include "Tile.h"
#include "../Player.h"

/*
Safes are the goal. Roll the combination to open them. When opened, draw a Loot, and increase the Guard's 
movement die by one on this floor and all those below it.
*/

//	CUANDO SALGA DE LA SAFE TILE, EL MODELO DEBE CHECKEAR EN LAS TILES (que esten boca arriba) DE LA FILA Y LA COLUMNA. 
//	SI EL NUMERO DE LA TILE NO APARECE EN LA COMBINATION, ES PORQUE ESTA "CRACKED"

class Safe : public Tile
{
public:
	Safe(int floor, int col, int row) : Tile(floor, col, row) { tokens = 0; tilesCracked = 0; cracked = false; };
	~Safe();

	/**
		Returns a vector of strings with the actions the player can do on the tile they are on
		@param p Player who wants to check the actions
	*/
	virtual vector<string>& getActions(void * player) override;

	/**
		Applies the action given to the player
		@param action Action to execute
		@param p Player who wants to do the action
	*/
	virtual void doAction(string action, void * player) override;

	/**
		Adds a number to the combination needed to crack the safe.
		@params tileNumber the number another tile adds to the safe combination.
	*/
	void addCombination( int tileNumber) { combination.push_back(tileNumber); };

public:
	unsigned int tokens;
	vector <int> combination;
	unsigned int tilesCracked;
	bool cracked;

	bool safeIsOpen() { return cracked; };
	void addToken() { if(tokens<6)	tokens++; };
	void removeToken() { if(tokens>0)	tokens--; };
	unsigned int getTokens() { return tokens; };

	/**
		Checks if the number given is one of the combination numbers. If so, removes that number from the list and returns the amount of
		numbers removed from the vector.
		@params number you want to try 
	*/
	int trySafeNumber(int number);
};

