#pragma once
#include <math.h>
#include <boost\preprocessor.hpp>
#include <boost\preprocessor\control\if.hpp>

#include <boost\ratio.hpp>

// Game frames per second
#define FPS 20

#define HOVER_TONE al_map_rgba(255,255,255,200)
#define PRESSED_TONE al_map_rgba(100,100,100,200)

#define NORMAL_COLOR  al_map_rgba_f(1,1,1,1
#define DISABLED_COLOR  al_map_rgba_f(0.3,0.3,0.3,1
#define HOVER_COLOR  al_map_rgba_f(1,1,1,0.8
#define CLICKED_COLOR  al_map_rgba_f(0.6,0.6,0.6,1

// Screen size
#define SCREEN_RATIO (16.0/9.0)
#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT (SCREEN_WIDTH / SCREEN_RATIO)

// Margins for board
#define LEFT_BOARD_MARGIN  (SCREEN_WIDTH * 0.03)
#define RIGHT_BOARD_MARGIN (SCREEN_WIDTH * 0.03)
#define UPPER_BOARD_MARGIN (SCREEN_HEIGHT * 0.03)
#define LOWER_BOARD_MARGIN (SCREEN_HEIGHT * 0.3)

// Board dimensions
#define BOARD_HEIGHT (SCREEN_HEIGHT - UPPER_BOARD_MARGIN - LOWER_BOARD_MARGIN)
#define BOARD_WIDTH  (SCREEN_WIDTH - LEFT_BOARD_MARGIN - RIGHT_BOARD_MARGIN)
#define BOARD_XPOS LEFT_BOARD_MARGIN 
#define BOARD_YPOS UPPER_BOARD_MARGIN

// Floor dimensions
#define FLOOR_SEPARATION (SCREEN_WIDTH * 0.025)
#define FLOOR_WIDTH (((BOARD_WIDTH - 4 * FLOOR_SEPARATION) / 3))
#define FLOOR_HEIGHT (BOARD_HEIGHT*0.8)

//Floor positions (Relative to board position)
#define FLOOR_YPOS 0 // Same y position for three floors

#define FLOOR1_XPOS (0 * (FLOOR_WIDTH + FLOOR_SEPARATION) + FLOOR_SEPARATION)
#define FLOOR2_XPOS (1 * (FLOOR_WIDTH + FLOOR_SEPARATION) + FLOOR_SEPARATION)
#define FLOOR3_XPOS (2 * (FLOOR_WIDTH + FLOOR_SEPARATION) + FLOOR_SEPARATION)

// Tile dimensions
// Calulated in file TileObserver.cpp because conditional cases are needed.
