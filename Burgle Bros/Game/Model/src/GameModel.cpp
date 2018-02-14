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


std::pair<Coord,Coord>
GameModel::getInitialGuardPos()
{
	BaseCard* c1 = board.getDeck(0)->getDeck()[board.getDeck(0)->getDeck().size() - 1];
	BaseCard* c2 = board.getDeck(0)->getDeck()[board.getDeck(0)->getDeck().size() - 2];
	return std::pair<Coord, Coord>(Coord::string2Coord(c1->getDescription()),Coord::string2Coord(c2->getDescription()));
}


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
	cout << endl << "______________________________________________________________________________" << endl;

#endif

}

void GameModel::setLocal()
{
	player1_.setLocal(true);
	player2_.setLocal(true);
	local = true;
}

void GameModel::setRemote()
{
	player1_.setLocal(true);
	player2_.setLocal(false);
	local = false;
}

bool GameModel::isRemote()
{
	return !local;
}
bool GameModel::isLocal()
{
	return local;
}

void GameModel::setInitialPosition(Coord c)
{
	player1_.setPosition(c);
	player2_.setPosition(c);
	player1_.getCurrentTile()->turnUp();

	board.getGuard(c.floor)->locateGuard();
	board.getTile(board.getGuard(c.floor)->getPos())->guardIs(true);
}
bool GameModel::gameOver()
{
	return player1_.getStealthTokens() == -1 || player2_.getStealthTokens() == -1;
}


void GameModel::endTurn()
{
	// Fullfil tile end of turn actions
	if (currentPlayer_->getPosition() != ROOF)
	{
		Tile * currentTile = board.getTile(currentPlayer_->getPosition());
		if (currentTile->getType() == MOTION)		// Disarm the alarm in the Motion Room
			((Motion *)currentTile)->disarm();
		else if (currentTile->getType() == THERMO && !currentPlayer_->has(MIRROR))
			((Thermo *)currentTile)->setAlarm(true);	//Set the alarm in Thermo Room
		for (auto &it : currentPlayer_->getCurrentTile()->getAdjacent())
		{
			if (it.floor < NUMBER_FLOORS)
			{
				if (board.getTile(it)->is(KEYPAD)) ((Keypad *)(board.getTile(it)))->clearAttempts();
			}
		}
	}

}

void GameModel::positionGuard()
{
	if (currentPlayer_->getPosition() != ROOF)
		board.getGuard(currentPlayer_->getPosition().floor)->positionGuard();
}
/**
Called after guard movement, it changes the turn
*/
void GameModel::changeTurn()
{
	currentPlayer_->resetActionTokens();
	currentPlayer_->useAbility(false);

	// Fullfil tile end of turn actions
	
	//??? NO HACE NADATile * currentTile = board.getTile(currentPlayer_->getPosition());
	
	swap(currentPlayer_, otherPlayer_);
	currentPlayer_->isPlaying(true);
	otherPlayer_->isPlaying(false);
	currentPlayer_->addTurn();
	otherPlayer_->addTurn();
	otherPlayer_->setPosition(otherPlayer_->getPosition());
	notify();
}

void GameModel::remotePlayerStarts()
{
	swap(currentPlayer_, otherPlayer_);
	currentPlayer_->isPlaying(true);
	otherPlayer_->isPlaying(false);
	//notify();
}





bool GameModel::doKittyAction(int dice)
{
	bool b = false;
	currentPlayer_->areLootsReady();
	if (currentPlayer_->has(PERSIAN_KITTY))
	{
		currentPlayer_->newAction("THROW_DICE", currentPlayer_->getPosition(), dice);
		cout << "Threw dice for kitty" << endl;
		if (dice == 1 || dice == 2)
		{
			cout << "Lost Persian Kitty" << endl;
			if (currentPlayer_->losePersianKitty()) b = true;
		}
	}
	return b;
}

bool GameModel::doChihuahuaAction(int dice)
{
	bool b = false;
	if (currentPlayer_->has(CHIHUAHUA))
	{
		currentPlayer_->newAction("THROW_DICE", currentPlayer_->getPosition(), dice);
		cout << "Threw dice for chihuahua" << endl;
		if (dice == 6)
		{
			currentPlayer_->getCurrentTile()->setAlarm(true);
			b = true;
		}
	}
	return b;

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
	board.getTile(board.getFloor(floor)->getGuard()->getPos())->guardIs(false);
	guardIsMoving_ = board.getFloor(floor)->moveGuard(currentPlayer_);
	board.getTile(board.getFloor(floor)->getGuard()->getPos())->guardIs(true);

	if (board.getTile(board.getFloor(floor)->getGuard()->getPos())->is(CAMERA) && board.getTile(board.getFloor(floor)->getGuard()->getPos())->isFlipped())
	{
		for (auto &it : board.getCameras())
		{
			if (!(it->getPos() == board.getFloor(floor)->getGuard()->getPos()) && it->getPos() == currentPlayer_->getPosition())
			{
				board.getTile(currentPlayer_->getPosition())->setAlarm(true);
			}
			else if (!(it->getPos() == board.getFloor(floor)->getGuard()->getPos()) && it->getPos() == otherPlayer_->getPosition())
			{

				board.getTile(otherPlayer_->getPosition())->setAlarm(true);
			}
		}
	}
	if (guardIsMoving_ == false)
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
			cout << "currently spying" << board[f].getPatrolDeck()->topCard()->getDescription() << endl;
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

void GameModel::initGuard4Network(Coord pos, Coord target)
{
	if (pos.floor == target.floor && pos.floor < NUMBER_FLOORS)
	{
		this->getBoard()->getFloor(pos.floor)->getPatrolDeck()->moveCardtoTop(target);
		this->getBoard()->getFloor(pos.floor)->getPatrolDeck()->moveCardtoTop(pos);
	}
}