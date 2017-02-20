#pragma once
#include "Configs.h"
#include "Floor.h"
#include "Player.h"
#include "Loot.h"

class Board
{
public:
	Board();
	~Board();
	void print()
	{
		for (int i = 0; i < 3; i++)
		{
			floor[i]->print();
			cout << endl;
		}
			
	};
private:
	Floor* floor[3];
	Player * players[2];
	Loot loots[3];

};

