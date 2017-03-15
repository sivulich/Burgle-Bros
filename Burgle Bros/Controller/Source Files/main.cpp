#include "../GameFSM.h"
#include "../../Model/Header Files/Player.h"
#include "../Header Files/controller.h"
#include <iostream>
#include <string>

int main()
{
	GameModel model;
	//GameFSM FSM(&model);
	Controller controller(&model, nullptr);
	model.setBoard();

	model.currentPlayer()->setPosition(Coord(0, 0, 0));
	model.currentPlayer()->setName(string("Pepe"));
	model.currentPlayer()->setCharacter(RAVEN);

	model.otherPlayer()->setPosition(Coord(0, 0, 0));
	model.otherPlayer()->setName(string("Gabriela"));
	model.otherPlayer()->setCharacter(PETERMAN);
	model.getBoard()[0].addAlarm(Coord(0, 2, 2));
	model.getBoard()[0].addAlarm(Coord(0, 1, 1));
	model.getBoard()[0].addAlarm(Coord(0, 2, 1));
	model.print();
	controller.startGame();

	return 0;
}