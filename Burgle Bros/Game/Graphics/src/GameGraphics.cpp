#include "GameGraphics.h"
#include "Button.h"
#include "Animations.h"
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
	current_screen = MENU;
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
	current_screen = MODE;
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Screen - Mode/background.jpg"));

	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/LOCAL.png")));
	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/REMOTE.png")));
	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/BACK.png"), 0, 617));
	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/EXIT.png"), 1134, 631));
}

void GameGraphics::showIPScreen()
{
	current_screen = IP;
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Screen - Mode/backgroundIP.jpg"));

	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/CONNECT.png"), 399, 389));
	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/BACK.png"), 0, 617));
	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/EXIT.png"), 1134, 631));

	if (textBox != nullptr)
		delete textBox;

	textBox = new Textbox(537, 325, 260, 44, string("./Graphics/Images/arial_narrow.ttf"));
	textBox->setMax(16);
	textBox->setFontColor(al_map_rgba_f(1, 1, 1, 0.5));
	textBox->setBoxColor(al_map_rgba_f(0, 0, 0, 0));
	cont->addObject(textBox);

}

void GameGraphics::showCreditsScreen()
{
	current_screen = CREDITS;
	cont->clear();
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Screen - Mode/background.jpg"));
	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/BACK.png")));
}

void GameGraphics::showRulesScreen()
{
	current_screen = RULES;
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Screen - Mode/background.jpg"));
	cont->addObject(new Image(string("./Graphics/Images/Screen - Mode/BACK.png")));
}



void GameGraphics::showSetupScreen(int player)
{
	current_screen = SETUP;
	cont->clear();
	// Load buttons and character
	Image*i;
	cont->setBackground(string("./Graphics/Images/Setup/background.jpg"));
	cont->addObject(new Image(string("./Graphics/Images/Setup/BACK.png"), 0, 616));
	cont->addObject(new Image(string("./Graphics/Images/Setup/NEXT.png"), 1136, 632));
	cont->addObject(new Image(string("./Graphics/Images/Setup/ACROBAT.png"), 53, 311));
	cont->addObject(new Image(string("./Graphics/Images/Setup/SPOTTER.png"), 147, 286));
	cont->addObject(new Image(string("./Graphics/Images/Setup/JUICER.png"), 254, 260));
	cont->addObject(new Image(string("./Graphics/Images/Setup/HAWK.png"), 361, 236));
	i = new Image(string("./Graphics/Images/Setup/ROOK.png"), 463, 184);
	i->disable();
	cont->addObject(i);
	cont->addObject(new Image(string("./Graphics/Images/Setup/HACKER.png"), 597, 190));
	cont->addObject(new Image(string("./Graphics/Images/Setup/RAVEN.png"), 714, 234));
	i = new Image(string("./Graphics/Images/Setup/RIGGER.png"), 880, 247);
	i->disable();
	cont->addObject(i);
	cont->addObject(new Image(string("./Graphics/Images/Setup/PETERMAN.png"), 1073, 311));

	// Load the textbox to enter the players name
	textBox = new Textbox(574, 645, 270, 44, string("./Graphics/Images/arial_narrow.ttf"));
	textBox->setFontColor(al_map_rgba_f(1, 1, 1, 0.5));
	textBox->setBoxColor(al_map_rgba_f(0, 0, 0, 0));
	cont->addObject(textBox);

	// Load player number
	if (player == 1)
		i = new Image(string("./Graphics/Images/Setup/PLAYER1.png"), 592, 120);

	else if (player == 2)
		i = new Image(string("./Graphics/Images/Setup/PLAYER2.png"), 592, 120);
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
	current_screen = GAME;
	cont->clear();
	cont->setBackground(string("./Graphics/Images/Screen - Game/background.jpg"));
	//And observers for the board and player
	board = new BoardObserver(model, cont);
	hud = new HudObserver(model, board, cont);
	textBox = new Textbox(CONSOLE_XPOS, -CONSOLE_HEIGHT, CONSOLE_WIDTH, CONSOLE_HEIGHT, string("./Graphics/Images/arial_narrow.ttf"));
	textBox->setFontColor(al_map_rgba_f(0, 0, 0, 1));
	textBox->setBoxColor(al_map_rgba_f(1, 1, 1, 1));
	cont->addObject(textBox);

	roof = new Image(string("../Game/Graphics/Images/HELIPAD.png"), ROOF_XPOS, ROOF_YPOS, TILE_SIZE / 4, TILE_SIZE / 4);
	roof->setName(string("COORDA1F3"));
	cont->addObject(roof);

}

void GameGraphics::setBorderVisible(bool b)
{
	if (cont != nullptr)
		cont->setBorderVisible(b);
}

string GameGraphics::getPlayerName()
{
	if (current_screen = SETUP)
		return textBox->getText();
}

string GameGraphics::getIP()
{
	if (current_screen = IP)
		return textBox->getText();
}
void GameGraphics::render()
{
	screen->draw();

}

void GameGraphics::update()
{
	if (current_screen = GAME)
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

void GameGraphics::zoomTile(Coord c)
{
	if (c != ROOF)
		board->zoomTile(c);
}
void GameGraphics::unZoomTile()
{
	board->unZoomTile();
}

void GameGraphics::askQuestion(string question)
{
	dialogBox = new DialogBox(DialogBox::YES_NO_MSG, question, cont);
}

void  GameGraphics::spyPatrolCard(int floorNumber)
{
	dialogBox = new DialogBox(DialogBox::YES_NO_MSG, "Do you want to keep the card on the top of the deck?", cont, false);
	showTopPatrol(floorNumber);

}
void GameGraphics::showOkMessage(string message)
{
	dialogBox = new DialogBox(DialogBox::OK_MSG, message, cont);
}
void GameGraphics::showCancelMessage(string message)
{
	dialogBox = new DialogBox(DialogBox::CANCEL_MSG, message, cont);
}

void GameGraphics::showTempMessage(string message)
{
	dialogBox = new DialogBox(DialogBox::TEMPORAL_INFO, message, cont);
}

void GameGraphics::removeDialogBox()
{
	if (dialogBox != nullptr)
		dialogBox->remove();
}

void GameGraphics::closeQuestion()
{
	/*	cont->removeObject(questionBox);
		delete QuestionBox;*/
}

void GameGraphics::toggleConsole()
{
	if (current_screen == GAME && textBox != nullptr)
	{
		if (textBox->isVisible())
			hideConsole();
		else
			showConsole();
	}
}

void GameGraphics::showConsole()
{
	if (current_screen == GAME && textBox != nullptr)
	{
		textBox->addAnimation(new MoveAnimation(pair<int, int>(CONSOLE_YPOS, CONSOLE_XPOS), 0.3));
		textBox->click();
	}

}

void GameGraphics::hideConsole()
{
	if (current_screen == GAME && textBox != nullptr)
	{
		textBox->addAnimation(new MoveAnimation(pair<int, int>(-CONSOLE_HEIGHT, CONSOLE_XPOS), 0.3));
		textBox->clear();
		textBox->unClick();
	}

}

bool GameGraphics::showingConsole()
{
	return textBox->getPos() == pair<int, int>(CONSOLE_YPOS, CONSOLE_XPOS);
}

bool GameGraphics::writingInConsole()
{
	return textBox->isClicked();
}

string GameGraphics::getConsoleText()
{
	if (current_screen == GAME && textBox != nullptr)
		return textBox->getText();
}

void GameGraphics::printInHud(string s)
{

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
	if (find(tiles.begin(), tiles.end(), ROOF) != tiles.end())
		roof->enable();
	else
		roof->disable();

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
