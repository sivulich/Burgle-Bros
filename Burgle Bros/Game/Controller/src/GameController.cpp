#include <GameController.h>
#include "./GameFSM.h"
#include <random>
#include <chrono>

GameController::GameController(GameModel * m, GameGraphics * g, BurgleNetwork * n) : stateMachine(new GameFSM(m, g, n, &guardTimer)), guardTimer(GUARD_SPEED), renderTimer(1.0 / FPS)
{
	network = n;
	model = m;
	graphics = g;

	// NUEVO

	connectedFlag = false;
	tileZoomMode = false;
	eventQueue << Keyboard::getEventSource() << Mouse::getEventSource() << graphics->getScreenEventSource();
	eventQueue << renderTimer.getEventSource() << guardTimer.getEventSource();
	al_init_user_event_source(&BurgleNetwork::networkEventSource);
	al_register_event_source(eventQueue.get(), &BurgleNetwork::networkEventSource);

	eventQueue << alx::EventSource(&BurgleNetwork::networkEventSource);

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

	//if (network != nullptr && model != nullptr)
	//{
	//	bool remote, connected, join;
	//	remote = model->isRemote();
	//	connected = network->isConnected();
	//	join = network->join();

	//	cout <<  remote << connected <<  join << endl;
	//}

	if (model != nullptr && model->isRemote() && network != nullptr)
	{
		//std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		remoteInput inp = network->getRemoteInput();
		//std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

		//cout << " Remote input time " << duration << " us." << endl;


		if (inp.action != NO_TYPE)
		{
			switch (inp.action)
			{
			case ACK:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::ack());
				break;
			case PASS:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::pass());
				break;
			case MOVE:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::move(inp.pos,inp.modifier));
				break;
			case PEEK:
				DEBUG_MSG("Safe number " <<inp.modifier);
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::peek(inp.pos,inp.modifier));
				break;
			case ERROR:
				DEBUG_MSG("ERROR: " << network->errMessage());
				break;

			case AGREE:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::yes());
				break;

			case DISAGREE:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::no());
				break;


			case INITIAL_G_POS:
				break;

			case SPENT_OK:
				if(inp.modifier == 'Y')
					static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::yes());
				else if((inp.modifier == 'N'))
					static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::no());
				break;

			case ADD_TOKEN:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::addToken());
				break;

			case USE_TOKEN:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::useToken());
				break;

			case THROW_DICE:
				break;

			case SAFE_OPENED:
				break;

			case CREATE_ALARM:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::createAlarm(inp.pos));
				break;

			case SPY_PATROL:
				break;

			case PLACE_CROW:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::placeCrow(inp.pos));
				break;

			case OFFER_LOOT:
				break;

			case REQUEST_LOOT:
				break;

			case PICK_UP_LOOT:
				break;

			case ROLL_DICE_FOR_LOOT:
				break;

			case GUARD_MOVEMENT:
				break;

			case WE_WON:
				break;

			case WE_LOST:
				break;

			case GAME_OVER:
				break;

			case QUIT:
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::close(true));
				break;

			case ERRO:
				break;

			}
			//return;
		}

	}

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
			case ALLEGRO_EVENT_MOUSE_AXES:	
				eventQueue.clear();
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
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_L)
					s = "PICK_UP_LOOT";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_K)
					s = "ACK";
				else if (event.getKeyboardKeycode() == ALLEGRO_KEY_W)
					s = "WAIT";
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
		case ALLEGRO_EVENT_TIMER:
			if (event.getTimer() == guardTimer)
				static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::moveGuard());
			else if (event.getTimer() == renderTimer)
			{
				ALLEGRO_MOUSE_STATE state;
				al_get_mouse_state(&state);
				graphics->hover(state.y, state.x);
				graphics->render();
			}

			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			s = "EXIT";
			break;
		}
	}
}

void GameController::processEvent()
{
	if (s.substr(0, 5) == string("COORD") && s.length() == 9)// String format: COORD[col][row]F[floor]
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
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::move());
	else if (s == "PEEK")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::peek());
	else if (s == "CREATE_ALARM")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::createAlarm());
	else if (s == "PLACE_CROW")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::placeCrow());
	else if (s == "SPY_PATROL")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::spyPatrol());
	else if (s == "THROW_DICE" || s == "CRACK_SAFE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::throwDice());
	else if (s == "ADD_TOKEN" || s == "ADD_DIE")
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
	else if (s == "DONE")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::done());
	else if (s == "OK")
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::ok());
	else if (s == "ACK")// este evento es de prueba
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::ack());
	else if (s == "WAIT")// este evento es de prueba
		static_pointer_cast<GameFSM>(stateMachine)->process_event(ev::waitForNetwork());

	//                       TRUCOS
	else if (s.substr(0, 8) == string("ADD_LOOT"))
		model->currentPlayer()->addLoot(toEnum_lootType(s.substr(9).c_str()));
	else if (s.substr(0, 4) == string("DROP"))
	{
		Loot * l = nullptr;
		if (s.substr(5) == string("GOLDBAR"))
			l = LootFactory().newLoot(GOLD_BAR);
		else if ((s.substr(5) == string("PERSIAN_KITTY")))
			l = LootFactory().newLoot(PERSIAN_KITTY);
		if (l != nullptr)
			model->getBoard()->getTile(model->currentPlayer()->getPosition())->setLoot(l);
	}
	else if (s.substr(0, 13) == string("SET_CHARACTER"))
	{
		std::cout << s.substr(14) << std::endl;
		model->currentPlayer()->setCharacter(s.substr(14));
	}
	else if (s.substr(0, 4) == string("MASK"))
	{
		//graphics->loadPlayerToken(s.substr(5));
	}
}