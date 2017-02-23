#pragma once
#include "Tile.h"

/*
When moving into a Keypad tile, you must guess the code. Take a die and toll it. If it is a 6, you enter 
the tile. If not, you will have to stay in the tile you came from. Once you roll a 6, put an open marker 
on the tile - any teammember can enter freely now that code is known. For each on the fourth attempt in 
a single turn you would roll 4 dice, but the next turn you would start back at 1 die. If you start the game 
or fall into this room, you may leave but must open it to get back in.
*/

//////////////////////////////////////////////////////////////////////////////////////////
/* EL JUEGO VA A TENER QUE RESETEAR LOS ATTEMPS CADA VEZ QUE UN PLAYER TERMINA SU TURNO */
//////////////////////////////////////////////////////////////////////////////////////////

class Keypad : public Tile
{
public:
	Keypad(int floor, int col, int row) : Tile(floor, col, row) { keyKnown = false; attemptsThisTurn = 0; };
	~Keypad();


	virtual vector<string>& getActions(Player p, Coord guardPos, Coord partnerPos);
	virtual void doAction(string action, Player p, Coord guardPos, Coord partnerPos);

private:
	unsigned int getAttempts() { return attemptsThisTurn; };
	void addAttempt() { ++attemptsThisTurn; };
	void clearAttempts() { attemptsThisTurn = 0; };

	bool keyKnown;
	unsigned int attemptsThisTurn;
};

