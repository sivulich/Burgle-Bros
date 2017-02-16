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
	Coord getCoord();

	/**

	*/
	PatrolCard(pair<int,int> coord);
	/**

	*/
	~PatrolCard();

private:
	pair<int,int> coord;
	bool flipped;
};

