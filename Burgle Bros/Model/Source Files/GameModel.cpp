#include "../Header Files/GameModel.h"
#include "../Header Files/Enumerations.h"
#include "../Header Files/Configs.h"
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
	cout << "______________________________________________________________________________" << endl;

#endif

}




bool GameModel::gameOver()
{
	return player1.getStealthTokens() == 0 || player2.getStealthTokens() == 0;
}

/**
Called after guard movement, it changes the turn
*/
void GameModel::changeTurn()
{
	swap(currentPlayer_, otherPlayer_);
}

bool GameModel::guardIsMoving()
{
	return guardIsMoving_;
}

void GameModel::moveGuard()
{
	int floor = currentPlayer_->getPosition().floor;

	guardIsMoving_ = board[floor].moveGuard();
}

bool GameModel::win()
{
	return player1.isOnRoof() && player2.isOnRoof() && player1.getLoots().size() + player2.getLoots().size() == 3;
}

void GameModel::setBoard()
{
	board.setBoard();
	board.setWalls();
}
void GameModel::setBoard(vector<tileType> tiles)
{
	board.setBoard(tiles);
	board.setWalls();
}
