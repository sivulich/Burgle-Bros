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
	currentPlayer_->useAbility(false);

	// Fullfil tile end of turn actions
	Tile * currentTile = board.getTile(currentPlayer_->getPosition());
	if (currentTile->getType() == MOTION)		// Disarm the alarm in the Motion Room
		((Motion *)currentTile)->disarm();
	else if (currentTile->getType() == THERMO)
		((Thermo *)currentTile)->setAlarm(true);	//Set the alarm in Thermo Room
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
// ME TENGO Q FIJAR SI HACER EL CHEQUEO DE CAMARAS UNS SUBFUNCION. NO lo pase al moveGuard del floor porq este no conoce a las camaras de otros pisos
void GameModel::moveGuard()
{
	int floor = currentPlayer_->getPosition().floor;
	board.getFloor(floor)->getGuard()->isMyTurn(true);
	if (board.getFloor(floor)->getGuard()->getPos() == NPOS)
	{
		board.getFloor(floor)->getGuard()->locateGuard();
		if (board.getFloor(floor)->tile(board.getFloor(floor)->getGuard()->getPos().col, board.getFloor(floor)->getGuard()->getPos().row)->is(CAMERA) && board.getFloor(floor)->tile(board.getFloor(floor)->getGuard()->getPos().col, board.getFloor(floor)->getGuard()->getPos().row)->isFlipped())
		{
			for (auto &it : board.getCameras())
			{
				if (!(it->getPos() == board.getFloor(floor)->getGuard()->getPos()) && it->getPos() == currentPlayer_->getPosition())
				{
					board[floor].tile(currentPlayer_->getPosition().col, currentPlayer_->getPosition().row)->setAlarm(true);
				}
				else if (!(it->getPos() == board.getFloor(floor)->getGuard()->getPos()) && it->getPos() == otherPlayer_->getPosition())
				{
					
					board.getFloor(otherPlayer_->getPosition().floor)->tile(otherPlayer_->getPosition().col, otherPlayer_->getPosition().row)->setAlarm(true);
				}
			}
		}
	}
	
	guardIsMoving_ = board.getFloor(floor)->moveGuard(currentPlayer_);
	if (board.getFloor(floor)->tile(board.getFloor(floor)->getGuard()->getPos().col, board.getFloor(floor)->getGuard()->getPos().row)->is(CAMERA) && board.getFloor(floor)->tile(board.getFloor(floor)->getGuard()->getPos().col, board.getFloor(floor)->getGuard()->getPos().row)->isFlipped())
	{
		for (auto &it : board.getCameras())
		{
			if (!(it->getPos() == board.getFloor(floor)->getGuard()->getPos()) && it->getPos() == currentPlayer_->getPosition())
			{
				board[floor].tile(currentPlayer_->getPosition().col, currentPlayer_->getPosition().row)->setAlarm(true);
			}
			else if (!(it->getPos() == board.getFloor(floor)->getGuard()->getPos()) && it->getPos() == otherPlayer_->getPosition())
			{

				board.getFloor(otherPlayer_->getPosition().floor)->tile(otherPlayer_->getPosition().col, otherPlayer_->getPosition().row)->setAlarm(true);
			}
		}
	}
	if(guardIsMoving_ == false)
		board.getFloor(floor)->getGuard()->isMyTurn(false);

	notify();
}

void GameModel::spyPatrol(unsigned f)
{
	if (f < 3)
	{
		if (currentPlayer_->getActionTokens() > 0 && currentPlayer_->getCharacter() == toEnum_characterType("SPOTTER") && (currentPlayer_->canIUseAbility()))
		{
			board[f].getPatrolDeck()->spyTop();
			currentPlayer_->removeActionToken();
			currentPlayer_->useAbility(true);
			cout << "currently spying" << board[f].getPatrolDeck()->topCard()->getDescription()<<endl;
		}
	}
};

void GameModel::stopSpying(unsigned f)
{
	if (f < 3)
	{
		board[f].getPatrolDeck()->noLongerSpied();
		cout << "Stopped spying" << endl;
	}
}
void GameModel::sendBottom(unsigned f)
{
	if (f < 3)
	{
		board[f].getPatrolDeck()->topToBottom();
		board[f].getPatrolDeck()->noLongerSpied();
		cout << "Sent top card to bottom" << endl;
	}
}

vector<Coord> GameModel::getTilesXDist(unsigned x, Player * p)
{
	Coord c = p->getPosition();
	return board[c.floor].getXDistanceTiles(x, c);
};

void GameModel::check4Cameras()
{
	board.checkCameras(currentPlayer_->getPosition());
	
};

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