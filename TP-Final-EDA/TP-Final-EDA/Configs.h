#pragma once
#include <cstdlib>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <map>
#include <utility>
#include <algorithm>
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

using namespace std;
using namespace alx;
#define Coord pair<int,int>	// <COL,FILA>
#define HOVER_TONE al_map_rgba(255,255,255,200)

/*CHARACTER SETTINGS*/
#define NUMBER_STEALTH_TOKENS 3
#define NUMBER_ACTION_TOKENS 4


typedef enum {THE_JUICER=0x20, THE_HACKER, THE_ACROBAT, THE_SPOTTER, THE_HAWK, THE_RAVEN, THE_PETERMAN } characterID;

typedef enum {
	ACK = 0x01, AGREE, DISAGREE, NAME = 0x10, NAME_IS, I_AM, INITIAL_G_POS, START_INFO,
	YOU_START = 0x20, I_START, PEEK = 0x30,	MOVE, SPENT_OK, ADD_TOKEN, USE_TOKEN, THROW_DICE,
	SAFE_OPENED, CREATE_ALARM, SPY_PATROL, PLACE_CROW, OFFER_LOOT, REQUEST_LOOT, PICK_UP_LOOT,
	PASS, ROLL_DICE_FOR_LOOT, GUARD_MOVEMENT, WE_WON = 0x40, WE_LOST, GAME_OVER, QUIT = 0xFE, ERROR = 0xFF
} actionID;

typedef enum{
	ATRIUM=0x01,CAMERA,COMPUTER_ROOM_F,COMPUTER_ROOM_L,COMPUTER_ROOM_M,DEADBOLT,FINGERPRINT,FOYER,
	KEYPAD,LABORATORY,LASER,LAVATORY,MOTION,SAFE,SCANNER,SECRET_DOOR,SERVICE_DUCT,STAIR,THERMO,WALKWAY} tileType;

typedef enum { TIARA = 0x30, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR } lootID;