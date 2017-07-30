#include "../../Model/Header Files/GameModel.h"
#include "../../ConsoleView/ConsoleView.h"
#include "../../Controller/Header Files/controller.h"
#include "../../Model/Header Files/Player.h"
#include "../Header Files/controller.h"
#include <iostream>
#include <string>

#pragma warning(disable:4996)
int main(void)
{
	GameModel model;
	ConsoleView view(&model);
	Controller c(&model,&view);
	model.setBoard();
	
	freopen("debugMSG.txt", "w+", stderr);
	
	model.currentPlayer()->setPosition(Coord(0, 0, 0));
	model.currentPlayer()->setName(string("Pepe"));
	model.currentPlayer()->setCharacter(JUICER);

	model.otherPlayer()->setPosition(Coord(0, 0, 0));
	model.otherPlayer()->setName(string("Gabriela"));
	model.otherPlayer()->setCharacter(JUICER);

	model.print();
	c.startGame();

	return 0;
}

/*
#include "../GameFSM.h"
#include <iostream>
#include <string>

int main()
{
	GameFSM FSM;

	FSM.start();
	//FSM.process_event(GameFSM::move());

	while (FSM.is_flag_active<GameFSM::gameClosed>() == false)
	{
		std::string s;
		std::cin >> s;


		if (s == "move")
			FSM.process_event(GameFSM::move());
		else if (s == "peek")
			FSM.process_event(GameFSM::peek());
		else if(s == "throwDice")
			FSM.process_event(GameFSM::throwDice());
		else if (s == "addToken")
			FSM.process_event(GameFSM::addToken ());
		else if (s == "useToken")
			FSM.process_event(GameFSM::useToken ());
		else if (s == "pass")
			FSM.process_event(GameFSM::pass());
		else if (s == "pause")
			FSM.process_event(GameFSM::pause());
		else if (s == "resume")
			FSM.process_event(GameFSM::resume());
		else if (s == "gameOver")
			FSM.process_event(GameFSM::gameOver());
		else if (s == "burglarsWin")
			FSM.process_event(GameFSM::burglarsWin());
		else if (s == "playAgain")
			FSM.process_event(GameFSM::playAgain());
		else if (s == "close")
			FSM.process_event(GameFSM::close());
		else if (s == "coord")
			FSM.process_event(GameFSM::coord());
		else if (s == "errorReceived")
			FSM.process_event(GameFSM::errorReceived());
		else if (s == "errorHandled")
			FSM.process_event(GameFSM::errorHandled());


		std::cout << std::endl << std::endl;
	}
	FSM.stop();
	return 0;
}
*/