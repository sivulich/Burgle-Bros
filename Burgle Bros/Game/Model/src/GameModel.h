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
		//player1_.setLocal(true);
		currentPlayer_  =  &player1_;
		otherPlayer_    =  &player2_;
		player1_.setLocal(true);
		player2_.setLocal(true);
		local = true;
		srand((unsigned int)time(NULL));
	};


	std::pair<Coord, Coord> getInitialGuardPos();

	//
	void setLocal();
	void setRemote();
	bool isRemote();
	bool isLocal();

	// Print game model in console
	void print();

	// Returns true if game is over
	bool gameOver();

	// Returns true if the burglars have won
	bool win();

	// Returns 3 or 4 depending on whether the gold bar is in play. (Counts loots carried by the player at that time)
	unsigned int lootsToWin();

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

	//
	void positionGuard();

	// Return true if guard is still moving
	bool guardIsMoving();

	//
	void endTurn();

	// Called after guard movement, it changes the turn of the player
	void changeTurn();
	void remotePlayerStarts();

	// Access to the current player
	Player * currentPlayer() { return currentPlayer_; };

	// Access to the other player
	Player * otherPlayer() { return otherPlayer_; };

	//
	void spyPatrol(unsigned f) ;

	//
	Coord stopSpying(unsigned f);

	// 
	void flipAll();

	//
	Coord sendBottom(unsigned f);

	//
	vector<Coord> getTilesXDist(unsigned x, Player * p);

	// 
	unsigned int getSafeNumber(Coord c);

	//
	void check4Cameras();

	//
	bool doKittyAction(int dice);

	//
	bool doChihuahuaAction(int dice);


	bool setSafeNumber(Coord c, unsigned int sNumber);


	//Initializes guard when recieving packets from network. Pos is the guard starting position, target the first patrol Card
	void initGuard4Network(Coord pos, Coord target);

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
	bool local;
};