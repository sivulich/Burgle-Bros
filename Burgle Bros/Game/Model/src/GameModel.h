#pragma once
#include <BaseModel.h>
#include <Board.h>
#include <Player.h>


// The game model inherits from base model class
// Every time something changes must call notify method so observer can update view
class GameModel : public BaseModel
{
public:
	GameModel() : player1_(&board,&player2_,1), player2_(&board, &player1_,2), board(&player1_, &player2_)
	{
		currentPlayer_  =  &player1_;
		otherPlayer_    =  &player2_;

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

	// Get the board tiles
	vector<tileType> getBoardSetup();

	// Sets the board, with defined tiles
	void setBoard(vector<tileType> tiles);

	// Set the initial position of the players
	void setInitialPosition(Coord c);

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

	//
	void spyPatrol(unsigned f) ;

	//
	void stopSpying(unsigned f);

	//
	void sendBottom(unsigned f);

	//
	vector<Coord> getTilesXDist(unsigned x, Player * p);

	//
	void check4Cameras();


	Board* getBoard() { return &board; };

	Player* player1() { return &player1_; };

	Player* player2() { return &player2_; };

private:	
	// Pointers to players
	Player* currentPlayer_;
	Player* otherPlayer_;

	Player player1_;
	Player player2_;

	Board board;
	
	bool guardIsMoving_;
};