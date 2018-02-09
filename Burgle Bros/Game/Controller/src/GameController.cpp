#include <GameController.h>
#include "./GameFSM.h"
#include <random>

GameController::GameController(GameModel * m, GameGraphics * g/*, BurgleNetwork * n*/) : stateMachine(new GameFSM(m, g/*, n*/, &guardTimer)), guardTimer(GUARD_SPEED), renderTimer(1.0 / FPS)
{
	//network = n;
	model = m;
	graphics = g;

	// NUEVO

	connectedFlag = false;
	tileZoomMode = false;
	eventQueue << Keyboard::getEventSource() << Mouse::getEventSource() << graphics->getScreenEventSource();
	eventQueue << renderTimer.getEventSource() << guardTimer.getEventSource();

	//	al_init_user_event_source(&BurgleNetwork::networkEventSource);
	//	al_register_event_source(eventQueue.get(), &BurgleNetwork::networkEventSource);

		//eventQueue << alx::EventSource(&BurgleNetwork::networkEventSource);

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
	s = "";
	/*if (network->newEvent())
	{
		ALLEGRO_EVENT e = network->getEvent();
		switch (e.type)
		{
		case NETWORK_CONNECTED:
			s = "NEXT";
		case NETWORK_INPUT:
			s = e.user.data1;
			break;
		}

	}
	else*/
	if (eventQueue.isEmpty() == false)
	{
		Event event = eventQueue.getEvent();

		switch (event.getType())
		{
		case ALLEGRO_EVENT_TIMER:
			if (event.getTimer() == guardTimer)
			{
				s = "MOVE";
			}
			else if (event.getTimer() == renderTimer)
				s = "RENDER";
			break;
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
			if (tileZoomMode == true)
				graphics->unZoomTile();

			s = "";
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			if (event.getKeyboardKeycode() == ALLEGRO_KEY_ESCAPE)
			{
				if (graphics->showingConsole() == true)
					graphics->hideConsole();
				else
					s = "EXIT";
			}

			if (event.getKeyboardKeycode() == ALLEGRO_KEY_ENTER)
			{
				if (graphics->writingInConsole() == true)
				{
					s = graphics->getConsoleText();
					graphics->hideConsole();
				}
			}
			else if (event.getKeyboardKeycode() == ALLEGRO_KEY_LCTRL)
				tileZoomMode = true;

			if (graphics->writingInConsole() == false)
			{
				if (event.getKeyboardKeycode() == ALLEGRO_KEY_M)
					s = "MOVE";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_P)
					s = "PEEK";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_Y)
					s = "YES";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_D)
					s = "CONTINUE_THROW";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_N)
					s = "NO";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_C)
					graphics->showConsole();
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_1)
					s = "FIRST_LOOT";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_2)
					s = "SECOND_LOOT";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_L)
					s = "PICK_UP_LOOT";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_Z)
					for (int f = 0; f < 3; f++)
						for (int i = 0; i < 4; i++)
							for (int j = 0; j < 4; j++)
							{
								if ((*model->getBoard())[f][i][j]->isFlipped() == false)
									(*model->getBoard())[f][i][j]->turnUp();
							}

			}


			// como string al_keycode_to_name(event.getKeyboardKeycode());
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (event.getKeyboardKeycode() == ALLEGRO_KEY_LCTRL)
			{
				tileZoomMode = false;
				graphics->unZoomTile();
			}
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
	else if (s == "CONNECT")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::connect());
	else if (s == "CANCEL")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::cancel());
	else if (s == "MOVE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::movee());
	else if (s == "PEEK")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::peek());
	else if (s == "CREATE_ALARM")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::createAlarm());
	else if (s == "PLACE_CROW")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::placeCrow());
	else if (s == "SPY_PATROL")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::spyPatrol());
	else if (s == "THROW_DICE")
	{
		if (model->currentPlayer()->isLocal() == false)
		{
			static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::throwDice());
		}
	}
	else if (s == "CRACK_SAFE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::throwDice());
	else if (s == "ADD_TOKEN")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::addToken());
	else if (s == "USE_TOKEN")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::useToken());
	else if (s == "REQUEST_LOOT")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::requestLoot());
	else if (s == "OFFER_LOOT")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::offerLoot());
	else if (s == "PICK_UP_LOOT")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::pickUpLoot());
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
	else if (s == "OK")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::ok());
	else if (s.substr(0, 5) == string("COORD") && s.length() == 9)// String format: COORD[col][row]F[floor]
	{
		Coord c = Coord(s[8] - '0', s[5] - 'A', s[6] - '0' - 1);
		if (tileZoomMode == true)
			graphics->zoomTile(c);
		else
			static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::coord(c));
	}
	else if (isInEnum_characterType(s.c_str()))
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::characterName(string(s)));
	else if (isInEnum_lootType(s.c_str()))
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::lootType(string(s)));

	//                       TRUCOS
	else if (s.substr(0, 8) == string("ADD_LOOT"))
	{
		model->currentPlayer()->addLoot(toEnum_lootType(s.substr(9).c_str()));
	}
	else if (s.substr(0, 4) == string("DROP"))
	{
		LootFactory factory;
		Loot * l = nullptr;
		if (s.substr(5) == string("GOLDBAR"))
			l = factory.newLoot(GOLD_BAR);
		else if ((s.substr(5) == string("PERSIAN_KITTY")))
			l = factory.newLoot(PERSIAN_KITTY);
		if (l != nullptr)
			model->getBoard()->getTile(model->currentPlayer()->getPosition())->setLoot(l);
	}
}

int  GameController::throwDice()
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(1, 6); // guaranteed unbiased
	return uni(rng);
}