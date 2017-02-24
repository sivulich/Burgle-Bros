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
		
	*/
	void setPlayer1Name(string& name);
	
	/**

	*/
	void setPlayer2Name(string& name);
	
	/**

	*/
	void startGame();
	
	/**

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
};

