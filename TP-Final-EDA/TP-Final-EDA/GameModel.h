#pragma once

#include "Board.h"
#include "Player.h"

class GameModel
{
public:
	GameModel();
	~GameModel();

private:
	Board board;
	Player player1;
	Player player2;


};

