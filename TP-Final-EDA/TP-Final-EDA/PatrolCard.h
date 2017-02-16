#pragma once
#include "Configs.h"

class PatrolCard
{

public:
	/**

	*/
	void flip();

	/**

	*/
	pair<char, char> getCoord();

	/**

	*/
	PatrolCard(COORD coord);
	/**

	*/
	~PatrolCard();

private:
	COORD coord;
	bool flipped;
};

