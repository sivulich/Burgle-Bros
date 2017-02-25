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
	currState = INPUT_1;
}





void
GameModel::input(string& in)
{
	if (currState == INPUT_1)
		command = in;
	else if (currState == INPUT_2)
		parameter = in;
	else if (currState == INPUT_3)
		confirmation = in;
}


bool GameModel::gameOver()
{
	return player1.getStealthTokens() == 0 || player2.getStealthTokens() == 0;
}



pair<action_ID, string> GameModel::getInput()
{
	string command, param;

	cin >> command >> param;

	return make_pair(toEnum_action_ID((char*)command.c_str()), param);
}

static bool checkParam(string& s)
{
	if (s.size() != 4)
		return false;
	if (s[2] != 'F')
		return false;
	if (s[0] - 'A' >= 0 && s[0] - 'A' <= 3 && s[1] - '1' >= 0 && s[1] - '1' <= 3 && s[3] - '1' >= 0 && s[3] - '1' <= 3)
		return true;
	return false;
}

void
GameModel::runStep()
{
	switch (currTurn) {
		case LOOT_1:
			currentPlayer = &player1;
			//DO LOOT STUFF
			break;
		case PLAYER_1:
			currentPlayer = &player1;
			if (command == "")
			{
				currState = INPUT_1;
				break;
			}
			switch (toEnum_action_ID((char *)command.c_str())) {
				case MOVE:
					if (parameter == "")
					{
						currState = INPUT_2;
						break;
					}
					if (checkParam(parameter))
					{
						int col = parameter[0] - 'A';
						int row = parameter[1] - '1';
						int floor = parameter[3] - '1';
						/*if((*(board[floor]))[col][row]->needsConfirmation(currentPlayer)==true)
						{
							currState=INPUT_3;
							break;
						}
						else*/
							confirmation="YES";
						
						if (confirmation == "YES")
						{
							(*(board[floor]))[col][row]->enterTile(currentPlayer);
						}
						else
							resetInput();
					}
					else
						resetInput();
					break;
				case PEEK:
					if (parameter == "")
					{
						currState = INPUT_2;
						break;
					}
					if (checkParam(parameter))
					{
						int col = parameter[0] - 'A';
						int row = parameter[1] - '1';
						int floor = parameter[3] - '1';
						(*(board[floor]))[col][row]->peek();
					}
					else
						resetInput();
					break;
			};
	}
}