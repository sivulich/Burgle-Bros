#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"
#include "Guard.h"

class GameModel : public BaseModel
{
public:
	GameModel() : player1(&board), player2(&board)
	{
		// Let the guard know the players
		///for (int i = 0; i < 3; i++)
		//	board[i]->getGuard()->setPlayers(&player1, &player2);

		currentPlayer_ = &player1;
		otherPlayer_ = &player2;
		srand(time(NULL));
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
		Returns true if the burglars have won
	*/
	bool win();

	/**
		Sets the board randomly // defined tiles
	*/
	void setBoard();
	void setBoard(vector<tileType> tiles);
	/**
		Move guard one step
	*/
	void moveGuard();

	/**
		Return true if guard is still moving
	*/
	bool guardIsMoving();
	
	/**
		Called after guard movement, it changes the turn
	*/
	void changeTurn();

	/**
	
	*/
	Player * currentPlayer() { return currentPlayer_; };

	/**

	*/
	Player * otherPlayer() { return otherPlayer_; };




private:	
	Player* currentPlayer_;
	Player* otherPlayer_;
	Player player1;
	Player player2;
	Board board;
	bool guardIsMoving_;
};

