#include "../../Header Files/Observers/GameObserver.h"

GameObserver::GameObserver(GameModel* g, int sHeight)
{
	game = g;
	screen= new Screen(sHeight, sHeight * 1280.0 / 720.0, string("../View/Images/BackGround.jpg"), false);
	screen->backgroundProperties(0, 0, double(sHeight) / 1080.0);
	cont= new Container(sHeight, sHeight * 1280.0 / 720.0);
	in=new localControler(screen);
	board= new BoardObserver(&game->getBoard(), cont);
	
	pl=new LocalPlayerObserver(game->getPlayer1(), board, cont);

	screen->addObject(cont);
	cont->setPosition(0, 0);
}

string
GameObserver::input()
{
	return in->input();
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
	delete in;
	delete board;
	delete pl;
	delete screen;
	delete cont;
}