#include "../Header Files/GameModel.h"
#include "../Header Files/Enumerations.h"

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



GameModel::GameModel()
{
}


GameModel::~GameModel()
{
}



bool GameModel::gameOver()
{

}


void GameModel::setPlayer1Name(string& name)
{

}


void GameModel::setPlayer2Name(string& name)
{

}

pair<action_ID, string> GameModel::getInput()
{
	string command, param;

	cin >> command >> param;

	return make_pair(toEnum_action_ID((char*)command.c_str()), param);
}
void GameModel::startGame()
{
	DEBUG_MSG("Game has started");

	while (!gameOver())
	{
		DEBUG_MSG("Make your move!!!!");

		pair<action_ID, string> command = getInput();

		switch (command.first)
		{
		case ACK:

			break;

		case AGREE:

			break;

		case DISAGREE:

			break;

		case NAME:

			break;

		case NAME_IS:

			break;

		case I_AM:

			break;

		case INITIAL_G_POS:

			break;

		case START_INFO:

			break;

		case YOU_START:

			break;

		case I_START:

			break;

		case PEEK:

			break;

		case MOVE:

			break;

		case SPENT_OK:

			break;

		case ADD_TOKEN:

			break;

		case USE_TOKEN:

			break;

		case THROW_DICE:

			break;

		case SAFE_OPENED:

			break;

		case CREATE_ALARM:

			break;

		case SPY_PATROL:

			break;

		case PLACE_CROW:

			break;

		case OFFER_LOOT:

			break;

		case REQUEST_LOOT:

			break;

		case PICK_UP_LOOT:

			break;

		case PASS:

			break;

		case ROLL_DICE_FOR_LOOT:

			break;

		case GUARD_MOVEMENT:

			break;

		case WE_WON:

			break;

		case WE_LOST:

			break;

		case GAME_OVER:

			break;

		case QUIT:

			break;

		case ERRO:

			break;

		default:

			break;
		}

	}
}