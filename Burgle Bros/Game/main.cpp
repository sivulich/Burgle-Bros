#include <GameController.h>
#include <GameGraphics.h>
//#include <BurgleNetwork.h>
#include <GameModel.h>
#include "GameState.h"

int main()
{
	//BurgleNetwork * network = new BurgleNetwork();
	GameModel* model = new GameModel();
	GameGraphics * graphics = new GameGraphics(model);

	GameController game(model, graphics);

	while (game.isRunning())
	{
		game.getInput();
		game.processEvent();
	}
	game.stop();

}