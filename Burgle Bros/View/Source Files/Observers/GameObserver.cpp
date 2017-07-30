#include "../../Header Files/Observers/GameObserver.h"

GameObserver::GameObserver(GameModel* g)
{
	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(0, &info);
	int sHeight = info.y2 - info.y1-40;
	//int sHeight = 1000;
	game = g;
	screen= new Screen(sHeight, sHeight * 1280.0 / 720.0, string("../View/Images/BackGround.jpg"), false);
	sHeight = screen->getHeight();
	screen->backgroundProperties(0, 0, double(sHeight) / 1080.0);
	cont= new Container(sHeight, sHeight * 1280.0 / 720.0);
	board= new BoardObserver(&game->getBoard(), cont);
	
	pl = new LocalPlayerObserver(game->getPlayer1(), board, cont);
	pl2 = new RemotePlayerObserver(game->getPlayer2(), board, cont);
	
	screen->addObject(cont);
	
	game->attach(this);
	cont->setPosition(0, 0);
	al_install_mouse();
	al_install_keyboard();
	
	events << Keyboard::getEventSource() << Mouse::getEventSource() << screen->getDisplay()->getEventSource();
}

string
GameObserver::input()
{
	if (events.isEmpty()==false)
	{
		Event event = events.getEvent();
		switch (event.getType())
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			{
				return "exit";
			}
			case ALLEGRO_EVENT_MOUSE_AXES:
			{
				screen->overYou(event.getMouseY(), event.getMouseX());
				return "";
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			{
				return screen->click(event.getMouseY(), event.getMouseX());
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			{
				screen->unClick(event.getMouseY(), event.getMouseX());
				return "";
			}
			case ALLEGRO_EVENT_KEY_DOWN:
			{
				if (event.getKeyboardKeycode() == ALLEGRO_KEY_ESCAPE)
					return "exit";
				string out;
				out+= al_keycode_to_name(event.getKeyboardKeycode());
				return out;
			}
		}
	}
	return "";
}

void
GameObserver::update()
{
	board->update();
	screen->draw();
}
GameObserver::~GameObserver()
{
	screen->removeObject(cont);
	cont->clear();
	delete board;
	delete pl;
	delete screen;
	delete cont;
}