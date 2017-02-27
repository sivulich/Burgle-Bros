#pragma once
#include "../Model/Header Files/Enumerations.h"


DEFINE_ENUM_WITH_CONVERSIONS(gameState,
(ROLL_FOR_LOOT)
(PLAYER_TURN)
(GUARD_TURN)
(EXIT))

DEFINE_ENUM_WITH_CONVERSIONS(gameEvent,
(MOVE)
(PEEK)
(ADD_TOKEN)
(TRHOW_DICE)
(NO_EVENT))

DEFINE_ENUM_WITH_CONVERSIONS(gameAction,
(DO_MOVE)
(DO_PEEK)
(DO_ADD_TOKEN)
(DO_THROW_DICE))

class GameFSM  
{
public:
	GameFSM();
	~GameFSM();
};





