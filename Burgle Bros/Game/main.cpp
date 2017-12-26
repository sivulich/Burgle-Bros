#include <GameController.h>
#include <GameGraphics.h>
#include <GameModel.h>

int main()
{
	GameModel* model = new GameModel();

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