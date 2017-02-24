#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"

class GameModel : public BaseModel
{
public:
	GameModel();
	~GameModel();

	/**
		
	*/
	bool gameOver();

	/**
		
	*/

	/**

	*/

	/**

	*/

	/**

	*/

	/**

	*/

	/**

	*/

	/**

	*/

	/**

	*/
private:
	Board board;
	Player player1;
	Player player2;
	Player* currentPlayer;
};