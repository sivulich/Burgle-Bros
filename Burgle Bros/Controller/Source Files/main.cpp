#include "../Header Files/GameModel.h"
#include "../../ConsoleView/ConsoleView.h"
#include "../../Controller/Header Files/controller.h"


int main(void)
{
	GameModel model;

	model.player1.setPosition(Coord(0, 0, 0));
	model.player1.setName(string("Pepe"));
	model.player1.setCharacter(RAVEN);

	model.player2.setPosition(Coord(0, 0, 0));
	model.player2.setName(string("Gabriela"));
	model.player2.setCharacter(PETERMAN);

	ConsoleView view(&model);
	Controller controller(&model, &view);

	controller.startGame();

	return 0;
}