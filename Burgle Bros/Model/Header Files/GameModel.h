#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"
#include "Configs.h"
class GameModel : public BaseModel
{
public:
	GameModel()
	{
		for (int i = 0; i < 3; i++)
		{
			board[i]->getGuard()->setPlayers(&player,player2)
		}
	};
	~GameModel();

	/**
		Returns true if game is over
	*/
	bool gameOver();
	
	/**
		FSM that receives input
	*/
	void input();
	
	/**
	
	*/
	void runStep()
	{
		if (input.state() == RUN)
		{
			switch (input.command())
			{

			}
		}
	}

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

private:
	Board board;
	Player player1;
	Player player2;

private:
	Player* currentPlayer;
	Player* otherPlayer;
};

