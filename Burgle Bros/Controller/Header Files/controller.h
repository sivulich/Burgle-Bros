#pragma once

#include "../../Model/Header Files/GameModel.h"
#include "../../ConsoleView/ConsoleView.h"
#include "../GameFSM.h"



/**
	Controller class which relates the model with the view.
	It has an event dispatcher and a finite state machine with the game logic
	whick modifies the model and renders the view
*/
class Controller
{
public:
	Controller(GameModel * m, ConsoleView * v)
	{
		model = m;
		view = v;
	}

	void startGame()
	{
		gameEvent event = NO_EVENT;

		while (FSM.status() != EXIT)
		{
			vector<string> actions = model->currentPlayer()->getActions();

			gameEvent event = getInput();
			if (event != NO_EVENT)
			{
				FSM.run(event);
				view->draw();
			}

		}
	}


private:
	gameEvent getInput()
	{
		// Si se movio el mouse, hoverear botones
		// Si se hizo click preguntar a la vista en que y traducir a evento
		// Si se apreto una tecla, traducir a evento 
		// Si sono algun timer (para dibujar, o el del movimiento del guardia), traducir a evento
		// Si llego paquete de jugador remoto, traducir a evento :)))))))))) MIERDA

		string input1, input2;
		cin >> input1 >> input2;
		ev = toEnum_gameEvent(input1.c_str());
		if (ev != NOT_IN_ENUM)
		{
			param = input2;
			return ev;
		}
		return NO_EVENT;	
	};

	gameEvent ev;
	string param;

	GameFSM FSM;
	GameModel * model;
	ConsoleView * view;
	
};