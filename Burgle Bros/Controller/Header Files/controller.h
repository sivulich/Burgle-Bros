#pragma once

#include "../../Model/Header Files/GameModel.h"
#include "../../ConsoleView/ConsoleView.h"
#include "../GameFSM.h"

DEFINE_ENUM_WITH_CONVERSIONS(gameState,
(ROLL_FOR_LOOT)
(PLAYER_TURN)
(GUARD_TURN)
(GAMEOVER)
(EXIT))

DEFINE_ENUM_WITH_CONVERSIONS(gameEvent,
(Move)
(Peek)
(Add_token)
(Use_token)
(Throw_dice)
(A_action)
(R_action)
(R_stealth)
(Move_guard)
(No_event))


/**
	Controller class which relates the model with the view.
	It has an event dispatcher and a finite state machine with the game logic
	whick modifies the model and renders the view
*/
class Controller
{
public:
	Controller(GameModel * m, ConsoleView * v) : FSM(m)
	{
		model = m;
		view = v;
	}

	void startGame()
	{
		FSM.start();
		while (FSM.isRunning())
		{
			getInput();
			FSM.processEvent(new movee());
		}
		FSM.stop();		
	}


private:
	void getInput()
	{
		// Si se movio el mouse, hoverear botones
		// Si se hizo click preguntar a la vista en que y traducir a evento
		// Si se apreto una tecla, traducir a evento 
		// Si sono algun timer (para dibujar, o el del movimiento del guardia), traducir a evento
		// Si llego paquete de jugador remoto, traducir a evento :)))))))))) MIERDA
		std::cin >> input;
	};

	gameEvent ev;
	string input;

	GameFSM FSM;
	GameModel * model;
	ConsoleView * view;
	
};