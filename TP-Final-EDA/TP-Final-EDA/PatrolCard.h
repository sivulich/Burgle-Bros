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
	PatrolCard(pair<char , char> coord);
	/**

	*/
	~PatrolCard();

private:
	pair<char, char> coord;
	bool flipped;
};

