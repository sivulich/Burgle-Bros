#include <GameController.h>
#include "./GameFSM.h"
GameController::GameController(GameModel * m,GameGraphics * g) : FSM(new GameFSM(m,g)) , renderTimer(1.0/30.0)
{
	model = m;
	graphics = g;
	
	eventQueue << Keyboard::getEventSource() << Mouse::getEventSource() << graphics->getScreenEventSource(); 	
};

void GameController::start()
{
	renderTimer.start();
	eventQueue << renderTimer.getEventSource();

	static_pointer_cast<GameFSM>(FSM)->start();
	// HACER TODAS LAS OTRAS COSAS NECESARIAS AL COMENZAR EL JUEGO
};


void GameController::stop()
{
	static_pointer_cast<GameFSM>(FSM)->stop();
	// HACER TODAS LAS OTRAS COSAS NECESARIAS AL TERMINAR EL JUEGO
};

bool GameController::isRunning()
{
	return static_pointer_cast<GameFSM>(FSM)->is_flag_active<GameFSM::gameClosed>() == false;
};


void GameController::getInput()
{
	// EN LA VERSION CON GRAFICOS ACA HAY QUE RECIBIR EVENTOS DE MOUSE, TECLADO, Y TIMERS 
	// (TIMERS DE RENDER, PARA MOVER EL GUADRIA, ETC...)
	// 
	// LOS CLICKS SE MANDAN A LA VISTA QUE DEVUELVE LO QUE SE APRETO Y ESTO SE INTERPRETA COMO 
	// UN EVENTO
	if (eventQueue.isEmpty() == false)
	{
		Event event = eventQueue.getEvent();

		switch (event.getType())
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				s = "CLOSE";
				break;

			case ALLEGRO_EVENT_MOUSE_AXES:
			
				graphics->hover(event.getMouseY(), event.getMouseX());
				s = "";
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				s = graphics->click(event.getMouseY(), event.getMouseX());
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				graphics->unclick(event.getMouseY(), event.getMouseX());
				s = "";
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
	
				if (event.getKeyboardKeycode() == ALLEGRO_KEY_ESCAPE)
					s = "CLOSE";

				// como string al_keycode_to_name(event.getKeyboardKeycode());
				break;
			case ALLEGRO_EVENT_TIMER:
				s = "RENDER";
		}
	}
}

void GameController::processEvent()
{
	if (s == "MOVE")
		static_pointer_cast<GameFSM>(FSM)->process_event(movee());
	else if (s == "PEEK")
		static_pointer_cast<GameFSM>(FSM)->process_event(peek());
	else if (s == "TROW_DICE")
		static_pointer_cast<GameFSM>(FSM)->process_event(throwDice());
	else if (s == "ADD_TOKEN")
		static_pointer_cast<GameFSM>(FSM)->process_event(addToken());
	else if (s == "UDE_TOKEN")
		static_pointer_cast<GameFSM>(FSM)->process_event(useToken());
	else if (s == "PASS")
		static_pointer_cast<GameFSM>(FSM)->process_event(pass());
	else if (s == "PAUSE")
		static_pointer_cast<GameFSM>(FSM)->process_event(pause());
	else if (s == "RESUME")
		static_pointer_cast<GameFSM>(FSM)->process_event(resume());
	else if (s == "GAME_OVER")
		static_pointer_cast<GameFSM>(FSM)->process_event(gameOver());
	else if (s == "BURGLARS_WIN")
		static_pointer_cast<GameFSM>(FSM)->process_event(burglarsWin());
	else if (s == "PLAY_AGAIN")
		static_pointer_cast<GameFSM>(FSM)->process_event(playAgain());
	else if (s == "CLOSE")
		static_pointer_cast<GameFSM>(FSM)->process_event(closee());
	else if (s == "ERROR_RECEIVED")
		static_pointer_cast<GameFSM>(FSM)->process_event(errorReceived());
	else if (s == "ERROR_HANDLED")
		static_pointer_cast<GameFSM>(FSM)->process_event(errorHandled());
	else if (s == "YES")
		static_pointer_cast<GameFSM>(FSM)->process_event(yes());
	else if (s == "NO")
		static_pointer_cast<GameFSM>(FSM)->process_event(no());
	else if (s.substr(0, 5) == "COORD" && s.length() == 8)
		static_pointer_cast<GameFSM>(FSM)->process_event(coord(Coord(s[5] - '0' - 1, s[6] - 'A', s[7] - '0' - 1)));
	else if (s == "RENDER")
		graphics->render();

}