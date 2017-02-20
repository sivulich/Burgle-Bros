#pragma once
#include <cstdlib>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <map>
#include <utility>
#include <algorithm>
#include <random>
#include "Enumerations.h"
#include "alx.hpp"
#include "alx\Bitmap.hpp"
#include "alx\Color.hpp"
#include "alx\Display.hpp"
#include "alx\EventQueue.hpp"
#include "alx\Event.hpp"
#include "alx\EventSource.hpp"
#include "alx\Mouse.hpp"
#include "alx\Keyboard.hpp"
#include "alx\Size.hpp"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x) do { { cerr << x << endl; } } while (0)
#else
#define DEBUG_MSG(x)
#endif


using namespace std;
using namespace alx;
#define Coord pair<int,int>	// <COL,FILA>
#define HOVER_TONE al_map_rgba(255,255,255,200)

/*CHARACTER SETTINGS*/
#define NUMBER_STEALTH_TOKENS 3
#define NUMBER_ACTION_TOKENS 4




DEFINE_ENUM_WITH_CONVERSIONS(characterID,

(THE_JUICER, 0x20)
(THE_HACKER, 0x21)
(THE_ACROBAT, 0x22)
(THE_SPOTTER, 0x23)
(THE_HAWK, 0x24)
(THE_RAVEN, 0x25)
(THE_PETERMAN, 0x26))

DEFINE_ENUM_WITH_CONVERSIONS(action_ID,

(ACK, 0x01)
(AGREE, 0x02)
(DISAGREE, 0x03)
(NAME, 0x10)
(NAME_IS, 0x11)
(I_AM, 0x12)
(INITIAL_G_POS, 0x13)
(START_INFO, 0x14)
(YOU_START, 0x20)
(I_START, 0x21)
(PEEK, 0x30)
(MOVE, 0x31)
(SPENT_OK, 0x32)
(ADD_TOKEN, 0x33)
(USE_TOKEN, 0x34)
(THROW_DICE, 0x35)
(SAFE_OPENED, 0x36)
(CREATE_ALARM, 0x37)
(SPY_PATROL, 0x38)
(PLACE_CROW, 0x39)
(OFFER_LOOT, 0x3A)
(REQUEST_LOOT, 0x3B)
(PICK_UP_LOOT, 0x3C)
(PASS, 0x3D)
(ROLL_DICE_FOR_LOOT, 0x3E)
(GUARD_MOVEMENT, 0x3F)
(WE_WON, 0x40)
(WE_LOST, 0x41)
(GAME_OVER, 0x42)
(QUIT, 0xFE)
(ERRO, 0xFF))


DEFINE_ENUM_WITH_CONVERSIONS(lootID,
(a)(g))

#define HOVER_TONE al_map_rgba(255,255,255,200)

