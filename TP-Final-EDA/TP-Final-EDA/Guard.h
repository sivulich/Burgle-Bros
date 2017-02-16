#pragma once
#include "Configs.h"
#include "Player.h"
class Guard
{
public:
	/**

	*/
	Guard();
	
	/**

	*/
	~Guard();

	/**

	*/
	void AddNextTarget (pair<int, int>);

	/**

	*/
	bool Move(Player Player1, Player Player2);

private:
	unsigned steps, currsteps;
	pair<int, int> pos;
	list<pair<int, int>> targets;
};

