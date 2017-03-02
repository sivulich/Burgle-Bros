#include "../../Model/Header Files/GameModel.h"
#include "../../ConsoleView/ConsoleView.h"
#include "../../Controller/Header Files/controller.h"
#include "../../Model/Header Files/Player.h"

#pragma warning(disable:4996)
int main(void)
{
	GameModel model;
	ConsoleView view(&model);
	model.setBoard();
	
	freopen("debugMSG.txt", "w+", stderr);
	
	model.currentPlayer()->setPosition(Coord(0, 0, 0));
	model.currentPlayer()->setName(string("Pepe"));
	model.currentPlayer()->setCharacter(RAVEN);

	model.otherPlayer()->setPosition(Coord(0, 0, 0));
	model.otherPlayer()->setName(string("Gabriela"));
	model.otherPlayer()->setCharacter(PETERMAN);

	model.print();


	Controller controller(&model, &view);

	controller.startGame();

	return 0;
}