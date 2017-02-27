#pragma once
#include "../Configs.h"

class Character, public BaseCard, public BaseModel
{
public:
	Character(characterType t) :type(t) {};
	~Character();

	characterType getType() { return  type; };
	bool is(characterType t) { return t == type; };

private:
	characterType type;
};

