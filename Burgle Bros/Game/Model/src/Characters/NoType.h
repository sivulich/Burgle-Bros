#pragma once

#include "Character.h"
class NoType : public Character
{
public:
	NoType() : Character(NO_CHARACTER_TYPE) {};;
	virtual string getAction(PlayerInterface * player) override;
};
