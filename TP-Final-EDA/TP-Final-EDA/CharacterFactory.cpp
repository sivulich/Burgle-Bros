#include "CharacterFactory.h"


Character * CharacterFactory::newCharacter(characterType type)
{
	switch (type)
	{
		case JUICER: return new Juicer;
		case HACKER: return new Hacker;
		case ACROBAT: return new Acrobat;
		case SPOTTER: return new Spotter;
		case HAWK: return new Hawk;
		case RAVEN: return new Raven;
		case PETERMAN: return new Peterman;
		default: return nullptr;
	}
}