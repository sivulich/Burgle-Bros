#include "../FSM(jullio).h"
#include "../../Model/Header Files/Player.h"
#include "../../View/Header Files/"

#include <iostream>
#include <string>

int main()
{
	GameModel model;
	GameGraphics graphics
	GameController game(&model);
	


	// A ESTA ALTURA SE SUPONE QUE LAS MAQUINAS YA ESTAN CONECTADAS
	// LOS NOMBRES DE CADA JUGADOR INGRESADOS
	game.start();

	while (game.isRunning())
	{
		game.getInput();
		game.processEvent();
	}

	game.stop();

	return 0;
}