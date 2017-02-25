#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"
#include "Configs.h"
class GameModel : public BaseModel
{
public:
	GameModel();
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

	Board board;
	Player player1;
	Player player2;
	FSM input;
private:
	Player* currentPlayer;
};

