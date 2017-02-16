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

#define HOVER_TONE al_map_rgba(255,255,255,200)
typedef enum{ATRIUM=0x01,CAMERA,COMPUTER_ROOM_F,COMPUTER_ROOM_L,COMPUTER_ROOM_M,DEADBOLT,FINGERPRINT,FOYER,KEYPAD,LABORATORY,LASER,LAVATORY,MOTION,SAFE,SCANNER,SECRET_DOOR,SERVICE_DUCT,STAIR,THERMO,WALKWAY} tileType;