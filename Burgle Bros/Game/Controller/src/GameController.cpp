#include <GameController.h>
#include "./GameFSM.h"

GameController::GameController(GameModel * m, GameGraphics * g) : stateMachine(new GameFSM(m, g, &guardTimer)), guardTimer(GUARD_SPEED), renderTimer(1.0 / FPS)
{

	model = m;
	graphics = g;

	eventQueue << Keyboard::getEventSource() << Mouse::getEventSource() << graphics->getScreenEventSource();
	eventQueue << renderTimer.getEventSource() << guardTimer.getEventSource();
	
	renderTimer.start();
	static_pointer_cast<GameFSM>(stateMachine)->start();
};




void GameController::stop()
{
	static_pointer_cast<GameFSM>(stateMachine)->stop();
	// HACER TODAS LAS OTRAS COSAS NECESARIAS AL TERMINAR EL JUEGO
};

bool GameController::isRunning()
{
	return static_pointer_cast<GameFSM>(stateMachine)->is_flag_active<GameFSM::gameClosed>() == false;
};


void GameController::getInput()
{
	if (eventQueue.isEmpty() == false)
	{
		Event event = eventQueue.getEvent();

		switch (event.getType())
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			s = "EXIT";
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
				s = "EXIT";
			else if (event.getKeyboardKeycode() == ALLEGRO_KEY_INSERT)
				s = "EXIT";
			//else if (event.getKeyboardKeycode() == ALLEGRO_KEY_LCTRL)
			//	graphics->zoomMode(true);


			// como string al_keycode_to_name(event.getKeyboardKeycode());
			break;
		case ALLEGRO_EVENT_KEY_UP:
			//if (event.getKeyboardKeycode() == ALLEGRO_KEY_LCTRL)
			//	graphics->zoomMode(false);
			break;
		case ALLEGRO_EVENT_TIMER:
			if (event.getTimer() == guardTimer)
			{
				s = "MOVE";
			}
			else if (event.getTimer() == renderTimer)
				s = "RENDER";
			break;

		}
	}
}

void GameController::processEvent()
{
	if (s == "RENDER")
		graphics->render();
	if (s == "START")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::start());
	else if (s == "CREDITS")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::credits());
	else if (s == "BACK")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::back());
	else if (s == "NEXT")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::next());
	else if (s == "RULES")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::rules());
	else if (s == "LOCAL")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::local());
	else if (s == "REMOTE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::remote());
	else if (s == "PLAY")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::play());


	else if (s == "MOVE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::movee());
	else if (s == "PEEK")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::peek());
	else if (s == "TROW_DICE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::throwDice());
	else if (s == "ADD_TOKEN")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::addToken());
	else if (s == "UDE_TOKEN")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::useToken());
	else if (s == "PASS")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::pass());
	else if (s == "PAUSE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::pause());
	else if (s == "RESUME")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::resume());
	else if (s == "GAME_OVER")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::gameOver());
	else if (s == "BURGLARS_WIN")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::burglarsWin());
	else if (s == "PLAY_AGAIN")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::playAgain());
	else if (s == "EXIT")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::close());
	else if (s == "ERROR_RECEIVED")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::errorReceived());
	else if (s == "ERROR_HANDLED")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::errorHandled());
	else if (s == "YES")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::yes());

	else if (s == "NO")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::no());

	else if (s.substr(0, 5) == string("COORD") && s.length() == 9)// String format: COORD[col][row]F[floor]
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::coord(Coord(s[8] - '0', s[5] - 'A', s[6] - '0' - 1)));

	else if(s == "ACROBAT" || s == "SPOTTER" || s == "JUICER" || s == "HAWK" || s == "HACKER" || s == "RAVEN" || s == "PETERMAN")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::characterName(string(s)));

	
		
}