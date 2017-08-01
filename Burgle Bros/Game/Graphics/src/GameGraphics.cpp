#include "GameGraphics.h"

GameGraphics::GameGraphics(GameModel * m)
{
	if (al_init() == true)
	{
		if (al_init_image_addon() && al_init_primitives_addon() &&	al_install_keyboard() && al_init_font_addon() && al_init_ttf_addon()
			&& al_install_mouse() && al_install_keyboard())
		{
			initOK_ = true;
			DEBUG_MSG_V("Correctly initialized allegro");




			ALLEGRO_MONITOR_INFO info;
			al_get_monitor_info(0, &info);
			
			
			int sHeight = 720;
			screen = new Screen(sHeight, sHeight * 1280.0 / 720.0, string("../View/Images/BackGround.jpg"), false);
			screen->backgroundProperties(0, 0, double(sHeight) / 1080.0);
			cont = new Container(sHeight, sHeight * 1280.0 / 720.0);
			board = new BoardObserver(m->getBoard(), cont);

			pl = new LocalPlayerObserver(m->getPlayer1(), board, cont);
			pl2 = new RemotePlayerObserver(m->getPlayer2(), board, cont);

			screen->addObject(cont);

			m->attach(this);// si?
			cont->setPosition(0, 0);

			


		}
		else
			DEBUG_MSG("Couldnt init allegro addons");
	}
	else
		DEBUG_MSG("Couldnt init allegro");
	initOK_ = false;

	model = m;
}

void GameGraphics::render()
{
	board->update();
	screen->draw();
}

void GameGraphics::update()
{
	board->update();
}

bool GameGraphics::hover(int y, int x)
{
	return screen->overYou(y,x);
}

string GameGraphics::click(int y, int x)
{
	return screen->click(y,x);
}

void GameGraphics::unclick(int y, int x)
{
	screen->unClick(y, x);
}



GameGraphics::~GameGraphics()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_system();

	screen->removeObject(cont);
	cont->clear();
	delete board;
	delete pl;
	delete screen;
	delete cont;


	// FALTAN COSAS

}
