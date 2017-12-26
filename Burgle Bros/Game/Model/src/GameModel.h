#pragma once
#include <BaseModel.h>
#include <Board.h>
#include <Player.h>


// The game model inherits from base model class
// Every time something changes must call notify method so observer can update view
class GameModel : public BaseModel
{
public:
	GameModel() : player1(&board,&player2), player2(&board, &player1), board(&player1, &player2)
	{
		currentPlayer_  =  &player1;
		otherPlayer_    =  &player2;

		srand(time(NULL));
	};

	// Print game model in console
	void print();

	// Returns true if game is over
	bool gameOver();

	// Returns true if the burglars have won
	bool win();

	// Sets the board, sorting the tiles randomly
	void setBoard();

	// Sets the board, with defined tiles
	void setBoard(vector<tileType> tiles);

	// Move the corresponding guard one step
	void moveGuard();

	// Return true if guard is still moving
	bool guardIsMoving();

	// Called after guard movement, it changes the turn of the player
	void changeTurn();

	// Access to the current player
	Player * currentPlayer() { return currentPlayer_; };


	// Access to the other player
	Player * otherPlayer() { return otherPlayer_; };

	// Tries to move current player to the given position
	bool moveTo(Coord c);

	Board* getBoard() { return &board; };

	Player* getPlayer1() { return &player1; };

	Player* getPlayer2() { return &player2; };

private:	
	// Pointers to players
	Player* currentPlayer_;
	Player* otherPlayer_;

	Player player1;
	Player player2;

	Board board;
	
	bool guardIsMoving_;
};