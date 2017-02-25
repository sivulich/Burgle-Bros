#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"
#include "Configs.h"

DEFINE_ENUM_WITH_CONVERSIONS(state, (INPUT_1)(INPUT_2)(INPUT_3)(RUN))
DEFINE_ENUM_WITH_CONVERSIONS(turn, (LOOT)(PLAYER)(GUARD))

class GameModel : public BaseModel
{
public:
	GameModel() : player1(&board), player2(&board)
	{
		for (int i = 0; i < 3; i++)
			board[i]->getGuard()->setPlayers(&player1, &player2);

		currState = INPUT_1;
		
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
	void input(string& in);

	/**

	*/
	void runStep();

	Board board;

	Player player1;
	Player player2;

private:
	Player* currentPlayer;
	Player* otherPlayer;

	/*Input params*/
	void resetInput() { command = parameter = confirmation = ""; currState = INPUT_1; };
	string command;
	string parameter;
	string confirmation;

	/*Fsm for input*/
	state currState;
	turn  currTurn;

};

