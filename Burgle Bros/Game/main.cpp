#include <GameController.h>
#include <GameGraphics.h>
#include <GameModel.h>

int main()
{
	GameModel* model = new GameModel();
	model->setBoard(); // LO TIENE QUE HACER LA FSM (para desues pasarle a la otra pc los tiles y eso)
	model->currentPlayer()->setPosition(Coord(0, 0, 0));
	model->currentPlayer()->setName(string("Pepe"));
	model->currentPlayer()->setCharacter(RAVEN);

	model->otherPlayer()->setPosition(Coord(0, 0, 0));
	model->otherPlayer()->setName(string("Gabriela"));
	model->otherPlayer()->setCharacter(PETERMAN);



	GameGraphics * graphics = new GameGraphics(model);
	GameController game(model,graphics);
	


	// A ESTA ALTURA SE SUPONE QUE LAS MAQUINAS YA ESTAN CONECTADAS
	// LOS NOMBRES DE CADA JUGADOR INGRESADOS
	game.start(); // arranca la fsm

	while (game.isRunning())
	{
		game.getInput();
		game.processEvent();
	}

	game.stop(); // para la fsm

	return 0;
}