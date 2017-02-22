#pragma once
#include "Enumerations.h"

DEFINE_ENUM_WITH_CONVERSIONS(characterType,
(JUICER, 0x20)
(HACKER)
(ACROBAT)
(SPOTTER)
(HAWK)
(RAVEN)
(PETERMAN))


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

