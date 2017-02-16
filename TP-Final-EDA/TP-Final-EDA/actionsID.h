#pragma once

/* Packet header definition */
#define ACK 0x01
#define AGREE 0x02
#define DISAGREE 0x03
#define NAME 0x10
#define NAME_IS 0x11
#define I_AM 0x12
#define INITIAL_G_POS 0x13
#define START_INFO 0x14
#define YOU_START 0x20
#define I_START 0x21
#define PEEK 0x30
#define MOVE 0x31
#define SPENT_OK 0x32
#define ADD_TOKEN 0x33
#define USE_TOKEN 0x34
#define THROW_DICE 0x35
#define SAFE_OPENED 0x36
#define CREATE_ALARM 0x37
#define SPY_PATROL 0x38
#define PLACE_CROW 0x39
#define OFFER_LOOT 0x3A
#define REQUEST_LOOT 0x3B
#define PICK_UP_LOOT 0x3C
#define PASS 0x3D
#define ROLL_DICE_FOR_LOOT 0x3E
#define GUARD_MOVEMENT 0x3F
#define WE_WON 0x40
#define WE_LOST 0x41
#define GAME_OVER 0x42
#define QUIT 0xFE
#define ERROR 0xFF
