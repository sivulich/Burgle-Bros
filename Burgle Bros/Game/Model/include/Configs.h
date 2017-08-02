#pragma once
#ifndef CONFIGS_H
#define CONFIGS_H

#include <cstdlib>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <map>
#include <utility>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>

#include <Enumerations.h>
#include <Coord.h>

//#include "../src/ConsoleColors.h"

#define DEBUG
//#define DEBUG_V

#ifdef DEBUG_V
#ifndef DEBUG
#define DEBUG
#endif // !DEBUG
#define DEBUG_MSG_V(x)  cerr << x <<endl
#else
#define DEBUG_MSG_V(x)
#endif

#ifdef DEBUG
#define DEBUG_MSG(x)  cerr << x<<endl
#else
#define DEBUG_MSG(x)
#endif

#ifdef DEBUG
#define DEBUG_LN_MSG(x)  cerr << x
#else
#define DEBUG_LN_MSG(x)
#endif


using namespace std;



/*CHARACTER SETTINGS*/
#define NUMBER_STEALTH_TOKENS 3
#define NUMBER_ACTION_TOKENS 4


DEFINE_ENUM_WITH_CONVERSIONS(action_ID,
(NO_TYPE,0x00)
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

DEFINE_ENUM_WITH_CONVERSIONS(lootType,
(TIARA, 0x30)
(PERSIAN_KITTY)
(PAINTING)
(MIRROR)
(KEYCARD)
(ISOTOPE)
(GEMSTONE)
(CURSED_GOBLET)
(CHIHUAHUA)
(GOLD_BAR))

DEFINE_ENUM_WITH_CONVERSIONS(tileType,
(ATRIUM, 0x01)
(CAMERA, 0x02)
(COMPUTER_ROOM_F, 0x03)
(COMPUTER_ROOM_L, 0x04)
(COMPUTER_ROOM_M, 0x05)
(DEADBOLT, 0x06)
(FINGERPRINT, 0x07)
(FOYER, 0x08)
(KEYPAD, 0x09)
(LABORATORY, 0x0A)
(LASER, 0x0B)
(LAVATORY, 0x0C)
(MOTION, 0x0D)
(SAFE, 0x0E)
(SCANNER, 0x0F)
(SECRET_DOOR, 0x10)
(SERVICE_DUCT, 0x11)
(STAIR, 0x12)
(THERMO, 0x13)
(WALKWAY, 0x14))

DEFINE_ENUM_WITH_CONVERSIONS(characterType,
(JUICER, 0x20)
(HACKER)
(ACROBAT)
(SPOTTER)
(HAWK)
(RAVEN)
(PETERMAN))


#endif //CONFIGS_H