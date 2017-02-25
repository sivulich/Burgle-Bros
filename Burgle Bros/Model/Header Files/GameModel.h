#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"
#include "Configs.h"
class GameModel : public BaseModel
{
public:
	GameModel() : player1(&board), player2(&board)
	{
		for (int i = 0; i < 3; i++)
			board[i]->getGuard()->setPlayers(&player1, &player2);
		
	};

	/**
		Returns true if game is over
	*/
	bool gameOver();
	
	
	/**
		Debug funcion to test in console
	*/
	pair<action_ID, string> getInput();
	/**

	*/

	/**

	*/

	/**

	*/

	/**

	*/


	Board board;
	Player player1;
	Player player2;

private:
	Player* currentPlayer;
	Player* otherPlayer;
};

