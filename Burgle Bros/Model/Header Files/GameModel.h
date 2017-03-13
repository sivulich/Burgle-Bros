#pragma once

#include "BaseModel.h"
#include "Board.h"
#include "Player.h"
#include "Guard.h"


class GameModel : public BaseModel
{
public:
	GameModel() : player1(&board,&player2), player2(&board, &player1), board(&player1, &player2)
	{
		currentPlayer_  =  &player1;
		otherPlayer_    =  &player2;

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
		Sets the board, sorting te tiles randomly
	*/
	void setBoard();

	/**
		Sets the board, with defined tiles
	*/
	void setBoard(vector<tileType> tiles);

	/**
		Move the correspongin guard one step
	*/
	void moveGuard();

	/**
		Return true if guard is still moving
	*/
	bool guardIsMoving();
	
	/**
		Called after guard movement, it changes the turn of the player
	*/
	void changeTurn();

	/**
		Access to the current player
	*/
	Player * currentPlayer() { return currentPlayer_; };

	/**
		Access to the other player
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

