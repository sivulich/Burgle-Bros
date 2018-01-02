#include "GameGraphics.h"
#include "Button.h"

GameGraphics::GameGraphics(GameModel * m)
{
	model = m;

	if (al_init() == true)
	{
		if (al_init_image_addon() && al_init_primitives_addon() && al_install_keyboard() && al_init_font_addon() && al_init_ttf_addon()
			&& al_install_mouse() && al_install_keyboard())
		{
			initOK_ = true;
			DEBUG_MSG_V("Correctly initialized allegro");

			ALLEGRO_MONITOR_INFO info;
			al_get_monitor_info(0, &info);



			// Create a window
			screen = new Screen(SCREEN_HEIGHT, SCREEN_WIDTH, string("../Game/Graphics/Images/BackGround.jpg"), false);
			screen->backgroundProperties(0, 0, SCREEN_HEIGHT / 1080.0);

			// Add a containter to the screen for all objects
			cont = new Container(SCREEN_HEIGHT, SCREEN_WIDTH, "Root container");
			screen->addObject(cont);
			cont->setPosition(0, 0);

			m->attach(this);
			showingGameScreen = false;
			showingSetupScreen = false;

		}
		else
			DEBUG_MSG("Couldnt init allegro addons");
	}
	else
		DEBUG_MSG("Couldnt init allegro");
	initOK_ = false;


}

void GameGraphics::showMenuScreen()
{
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Menu/background.jpg"));

	cont->addObject(new Button(string("START"),
		string("./Graphics/Images/Menu/start.png"),
		string("./Graphics/Images/Menu/startHover.png"),
		string("./Graphics/Images/Menu/startClicked.png")));
	cont->addObject(new Button(string("CREDITS"),
		string("./Graphics/Images/Menu/credits.png"),
		string("./Graphics/Images/Menu/creditsHover.png"),
		string("./Graphics/Images/Menu/creditsClicked.png")));
	cont->addObject(new Button(string("RULES"),
		string("./Graphics/Images/Menu/rules.png"),
		string("./Graphics/Images/Menu/rulesHover.png"),
		string("./Graphics/Images/Menu/rulesClicked.png")));
	cont->addObject(new Button(string("EXIT"),
		string("./Graphics/Images/Menu/exit.png"),
		string("./Graphics/Images/Menu/exitHover.png"),
		string("./Graphics/Images/Menu/exitClicked.png")));

	/*cont->addObject(new Image(string("./Graphics/Images/Menu/start.png"), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	cont->addObject(new Image(string("./Graphics/Images/Menu/credits.png"), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	cont->addObject(new Image(string("./Graphics/Images/Menu/rules.png"), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	cont->addObject(new Image(string("./Graphics/Images/Menu/exit.png"), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));*/

}

void GameGraphics::showModeScreen()
{
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Mode/background.jpg"));

	cont->addObject(new Image(string("./Graphics/Images/Mode/LOCAL.png")));
	cont->addObject(new Image(string("./Graphics/Images/Mode/REMOTE.png")));
	cont->addObject(new Image(string("./Graphics/Images/Mode/BACK.png")));
	cont->addObject(new Image(string("./Graphics/Images/Mode/EXIT.png")));
}


void GameGraphics::showCreditsScreen()
{
	cont->clear();
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Mode/background.jpg"));
	cont->addObject(new Image(string("./Graphics/Images/Mode/BACK.png")));
}

void GameGraphics::showRulesScreen()
{
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Mode/background.jpg"));
	cont->addObject(new Image(string("./Graphics/Images/Mode/BACK.png")));
}



void GameGraphics::showSetupScreen(int player)
{
	showingSetupScreen = true;
	cont->clear();
	Image*i;
	cont->setBackground(string("./Graphics/Images/Setup/background.jpg"));
	cont->addObject(new Image(string("./Graphics/Images/Setup/BACK.png"), 0, 616));
	cont->addObject(new Image(string("./Graphics/Images/Setup/NEXT.png"),1136,632));
	cont->addObject(new Image(string("./Graphics/Images/Setup/ACROBAT.png"),53,311));
	cont->addObject(new Image(string("./Graphics/Images/Setup/SPOTTER.png"),147,286));
	cont->addObject(new Image(string("./Graphics/Images/Setup/JUICER.png"),254,260));
	cont->addObject(new Image(string("./Graphics/Images/Setup/HAWK.png"),361,236));
	i = new Image(string("./Graphics/Images/Setup/ROOK.png"),463,184);
	i->disable();
	cont->addObject(i);
	cont->addObject(new Image(string("./Graphics/Images/Setup/HACKER.png"),597,190));
	cont->addObject(new Image(string("./Graphics/Images/Setup/RAVEN.png"),714,234));
	i = new Image(string("./Graphics/Images/Setup/RIGGER.png"),880,247);
	i->disable();
	cont->addObject(i);
	cont->addObject(new Image(string("./Graphics/Images/Setup/PETERMAN.png"),1073,311));

	textBox = new Textbox(574, 645, 270, 44, string("./Graphics/Images/arial_narrow.ttf"));
	textBox->setFontColor(al_map_rgba_f(1,1,1,0.5));
	textBox->setBoxColor(al_map_rgba_f(0,0,0,0));
	cont->addObject(textBox);

	if (player == 1)
		i = new Image(string("./Graphics/Images/Setup/PLAYER1.png"),592,120);

	else if (player == 2)
		i = new Image(string("./Graphics/Images/Setup/PLAYER2.png"),592, 120);
	else
		i = nullptr;

	if (i != nullptr)
	{
		i->setHoverable(false);
		i->setClickable(false);
		cont->addObject(i);
	}
}

// 
void GameGraphics::showGameScreen()
{
	showingGameScreen = true;
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Screen - Game/background.jpg"));
	// And observers for the board and player
	board = new BoardObserver(model, cont);
	hud = new HudObserver(model, board, cont);
}

void GameGraphics::setBorderVisible(bool b)
{
	if (cont != nullptr)
		cont->setBorderVisible(b);
}

string GameGraphics::getPlayerName()
{
	if (showingSetupScreen)
		return textBox->getText();
}

void GameGraphics::render()
{
	screen->draw();
}

void GameGraphics::update()
{
	if (showingGameScreen)
	{
		board->update();
		hud->update();
	}

}

bool GameGraphics::hover(int y, int x)
{
	return screen->overYou(y, x);
}

string GameGraphics::click(int y, int x)
{
	return screen->click(y, x);
}

void GameGraphics::unclick(int y, int x)
{
	screen->unClick(y, x);
}

void GameGraphics::askQuestion(string question)
{
	//questionBox = new QuestionBox(question);
	//cont->addObject(question);
}

void GameGraphics::closeQuestion()
{
	//cont->removeObject(questionBox);
	//delete QuestionBox;
}
void GameGraphics::setTilesClickable(vector<Coord> tiles)
{
	for (int f = 0; f < 3; f++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (find(tiles.begin(), tiles.end(), Coord(f, i, j)) != tiles.end())
					(*board)[f][i][j]->enable();
				else
					(*board)[f][i][j]->disable();
			}
		}

	}
}

void GameGraphics::setAllClickable()
{
	for (int f = 0; f < 3; f++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				(*board)[f][i][j]->enable();
		}

	}
}

GameGraphics::~GameGraphics()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_system();

	screen->removeObject(cont);
	cont->clear();
	delete board;
	//delete pl;
	delete screen;
	delete cont;


	// FALTAN COSAS

}
