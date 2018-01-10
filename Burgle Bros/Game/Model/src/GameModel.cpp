#include "./GameModel.h"
#include "./Enumerations.h"
#include "./Configs.h"
/*
DEFINE_ENUM_WITH_CONVERSIONS(action_ID,
(ACK, 0x01)
(AGREE, 0x02)
(DISAGREE, 0x03)
(NAME, 0x10)
(NAME_IS, 0x11)
(I_AM, 0x12)
(INITIAL_G_POS, 0x13)
(START_INFO, 0x14)
(YOU_START, 0x20)
(I_START, 0x21)
(PEEK, 0x30)
(MOVE, 0x31)
(SPENT_OK, 0x32)
(ADD_TOKEN, 0x33)
(USE_TOKEN, 0x34)
(THROW_DICE, 0x35)
(SAFE_OPENED, 0x36)
(CREATE_ALARM, 0x37)
(SPY_PATROL, 0x38)
(PLACE_CROW, 0x39)
(OFFER_LOOT, 0x3A)
(REQUEST_LOOT, 0x3B)
(PICK_UP_LOOT, 0x3C)
(PASS, 0x3D)
(ROLL_DICE_FOR_LOOT, 0x3E)
(GUARD_MOVEMENT, 0x3F)
(WE_WON, 0x40)
(WE_LOST, 0x41)
(GAME_OVER, 0x42)
(QUIT, 0xFE)
(ERRO, 0xFF))*/





void GameModel::print()
{
#ifdef DEBUG
	system("CLS");
	cout << "______________________________________________________________________________" << endl;

	board.print();
	cout << "Current Player:" << endl;
	currentPlayer()->print();

//	cout << "Other Player:" << endl;
//	otherPlayer()->print();

	cout << "Guard" << endl;
	for (int i = 0; i < 3; i++)
	{
		board[i].getGuard()->print();
	}
	cout <<  endl << "______________________________________________________________________________" << endl;

#endif

}


void GameModel::setInitialPosition(Coord c)
{
	player1_.setPosition(c);
	player2_.setPosition(c);
}
bool GameModel::gameOver()
{
	return player1_.getStealthTokens() == 0 || player2_.getStealthTokens() == 0;
}

/**
Called after guard movement, it changes the turn
*/
void GameModel::changeTurn()
{
	currentPlayer_->resetActionTokens();
	swap(currentPlayer_, otherPlayer_);
	currentPlayer_->isPlaying(true);
	otherPlayer_->isPlaying(false);
	currentPlayer_->addTurn();
	otherPlayer_->addTurn();
	notify();
}

bool GameModel::guardIsMoving()
{
	return guardIsMoving_;
}

void GameModel::moveGuard()
{
	int floor = currentPlayer_->getPosition().floor;
	board[floor].getGuard()->isMyTurn(true);

	guardIsMoving_ = board[floor].moveGuard();
	if(guardIsMoving_ == false)
		board[floor].getGuard()->isMyTurn(false);

	notify();
}

bool GameModel::win()
{
	// If both players are on the roof and have all the loots, the game has finished
	return player1_.isOnRoof() && player2_.isOnRoof() && player1_.getLoots().size() + player2_.getLoots().size() == 3;
}

void GameModel::setBoard()
{
	board.setBoard();
	board.setWalls();
	board.parseBoard();
}

vector<tileType> GameModel::getBoardSetup()
{
	return board.getTileSetup();
}

void GameModel::setBoard(vector<tileType> tiles)
{
	board.setBoard(tiles);
	board.setWalls();
	board.parseBoard();

}