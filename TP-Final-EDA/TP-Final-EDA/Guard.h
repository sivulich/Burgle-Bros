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
	void AddNextTarget ( COORD);

	/**

	*/
	bool Move(Player Player1, Player Player2);

private:
	unsigned steps, currsteps;
	COORD pos;
	list<COORD> targets;
};

