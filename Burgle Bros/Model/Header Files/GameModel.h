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
		// Let the guard know the players
		for (int i = 0; i < 3; i++)
			board[i]->getGuard()->setPlayers(&player1, &player2);
	};

	/**
		Print game model in console
	*/
	void print();

	/**
		Returns true if game is over
	*/
	bool gameOver();

	/**
	
	*/
	Player * currentPlayer() { return currentPlayer_; };

	/**

	*/
	Player * otherPlayer() { return otherPlayer_; };


	Player player1;
	Player player2;
	Board board;

private:	
	Player* currentPlayer_;
	Player* otherPlayer_;
};

