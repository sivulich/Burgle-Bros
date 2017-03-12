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

	
	controller.startGame();

	return 0;
}