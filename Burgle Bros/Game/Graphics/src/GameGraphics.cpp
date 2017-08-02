#include "GameGraphics.h"
#include <GraphicsDefs.h>

GameGraphics::GameGraphics(GameModel * m)
{
	model = m;

	if (al_init() == true)
	{
		if (al_init_image_addon() && al_init_primitives_addon() &&	al_install_keyboard() && al_init_font_addon() && al_init_ttf_addon()
			&& al_install_mouse() && al_install_keyboard())
		{
			initOK_ = true;
			DEBUG_MSG_V("Correctly initialized allegro");




			ALLEGRO_MONITOR_INFO info;
			al_get_monitor_info(0, &info);
			
			
	
			// Create a window
			screen = new Screen(SCREEN_HEIGHT, SCREEN_WIDTH, string("../View/Images/BackGround.jpg"), false);
			screen->backgroundProperties(0, 0, SCREEN_HEIGHT / 1080.0);

			// A containter for all objects
			cont = new Container(SCREEN_HEIGHT, SCREEN_WIDTH);
			screen->addObject(cont);
			cont->setPosition(0, 0);


			// And observers for the board and player
			board = new BoardObserver(m->getBoard(), cont);
			pl = new LocalPlayerObserver(m->getPlayer1(), board, cont);
			pl2 = new RemotePlayerObserver(m->getPlayer2(), board, cont);

			
			//Attach graphics to the model
			m->attach(this);
			
		}
		else
			DEBUG_MSG("Couldnt init allegro addons");
	}
	else
		DEBUG_MSG("Couldnt init allegro");
	initOK_ = false;

	
}

void GameGraphics::render()
{

	screen->draw();
}

void GameGraphics::update()
{
	board->update();
	pl->update();
	pl2->update();
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


void GameGraphics::setTilesClickable(vector<Coord> tiles)
{

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
