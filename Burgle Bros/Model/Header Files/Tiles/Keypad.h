#pragma once
#include "Tile.h"

/*
When moving into a Keypad tile, you must guess the code. Take a die and toll it. If it is a 6, you enter 
the tile. If not, you will have to stay in the tile you came from. Once you roll a 6, put an open marker 
on the tile - any teammember can enter freely now that code is known. For each on the fourth attempt in 
a single turn you would roll 4 dice, but the next turn you would start back at 1 die. If you start the game 
or fall into this room, you may leave but must open it to get back in.
*/

class Keypad : public Tile
{
public:
	Keypad(int floor, int col, int row) : Tile(floor, col, row) {};
	~Keypad();


private:
	unsigned int getAttempts() { return attempts; };
	void correctKey() { keyKnown = true; };
	void addAttempt() { ++attempts; };
	void clearAttempts() { attempts = 0; };
	bool keyKnown;
	unsigned int attempts;
};

