#pragma once
#include "Floor.h"
#include "Configs.h"

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
};

