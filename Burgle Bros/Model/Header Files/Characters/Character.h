#pragma once
#include "../Configs.h"

class Character
{
public:
	Character();
	~Character();

	characterType getType() { return  type; };
	bool is(characterType t) { return t == type; };

private:
	characterType type;
};

