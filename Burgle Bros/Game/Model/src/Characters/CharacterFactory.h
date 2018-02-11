#pragma once
#include "Character.h"
#include "Acrobat.h"
#include "Juicer.h"
#include "Hacker.h"
#include "Spotter.h"
#include "Hawk.h"
#include "Raven.h"
#include "Peterman.h"
#include "NoType.h"

class CharacterFactory
{
public:
	CharacterFactory() {};

	static Character * newCharacter(characterType type);
};

