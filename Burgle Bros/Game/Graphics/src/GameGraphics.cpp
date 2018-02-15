#include "./GameGraphics.h"

GameGraphics::GameGraphics(GameModel * m)
{
	if (al_init() == true)
	{
		if (al_init_image_addon() && al_init_primitives_addon() && al_install_keyboard() && al_init_font_addon() && al_init_ttf_addon()
			&& al_install_mouse() && al_install_keyboard() && al_install_audio())
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
			ipScreen = new IpScreen(cont);
			screens.push_back(ipScreen);
			modeScreen = new ModeScreen(cont);
			screens.push_back(modeScreen);
			menuScreen = new MenuScreen(cont);
			screens.push_back(menuScreen);
			creditScreen = new CreditScreen(cont);
			screens.push_back(creditScreen);
			setupScreen = new SetupScreen(cont);
			screens.push_back(setupScreen);
			rulesScreen = new RulesScreen(cont);
			screens.push_back(rulesScreen);
			gameScreen = new Container(SCREEN_HEIGHT, SCREEN_WIDTH, "GAME_SCREEN");
			gameScreen->setVisible(false);
			gameScreen->setPosition(0, 0);
			cont->addObject(gameScreen);
			screens.push_back(gameScreen);
			screen->addObject(cont);
			cont->setPosition(0, 0);
			current_screen = MENU;
			if (m != nullptr)
				setModel(m);
			
		}
		else
			DEBUG_MSG("Couldnt init allegro addons");
	}
	else
		DEBUG_MSG("Couldnt init allegro");
	initOK_ = false;


}

void GameGraphics::setModel(GameModel * m)
{
	model = m;
	m->attach(this);
}

//Screens Con nuevo Metodo
void GameGraphics::showMenuScreen()
{
	current_screen = MENU;
	setAllNotVisible();
	menuScreen->setVisible(true);
	if(!alreadyPlaying && (alreadyPlaying=true)==true)
		sound.playbackgroundMusic();
}

void GameGraphics::showModeScreen()
{
	current_screen = MODE;
	cont->addObject(modeScreen);
	setAllNotVisible();
	modeScreen->setVisible(true);
}

void GameGraphics::showIPScreen()
{
	current_screen = IP;
	setAllNotVisible();
	ipScreen->setVisible(true);

}

void GameGraphics::showCreditsScreen()
{
	current_screen = CREDITS;
	setAllNotVisible();
	creditScreen->setVisible(true);
}

void GameGraphics::showSetupScreen(int player)
{
	current_screen = SETUP;
	setAllNotVisible();
	setupScreen->setVisible(true);
	// Load player number
	if (player == 1)
		setupScreen->showPlayer1();

	else if (player == 2)
	{
		setupScreen->showPlayer2(string(toString(model->player1()->getCharacter())));
	}
}

void GameGraphics::showRulesScreen()
{
	current_screen = RULES;
	setAllNotVisible();
	rulesScreen->setVisible(true);
}


 
void GameGraphics::showGameScreen()
{
	current_screen = GAME;
	setAllNotVisible();
	gameScreen->setBackground(string("./Graphics/Images/Screen - Game/background.jpg"));
	//And observers for the board and player
	board = new BoardObserver(model, gameScreen);
	hud = new HudObserver(model, board, gameScreen);
	textBox = new Textbox(CONSOLE_XPOS, -CONSOLE_HEIGHT, CONSOLE_WIDTH, CONSOLE_HEIGHT, string("./Graphics/Images/arial_narrow.ttf"));
	textBox->setFontColor(al_map_rgba_f(0, 0, 0, 1));
	textBox->setBoxColor(al_map_rgba_f(1, 1, 1, 1));
	gameScreen->addObject(textBox);

	roof = new Image(string("../Game/Graphics/Images/HELIPAD.png"), ROOF_XPOS, ROOF_YPOS, TILE_SIZE / 4, TILE_SIZE / 4);
	roof->setName(string("COORDA1F3"));
	gameScreen->addObject(roof);

	hudText = new Text(string("./Graphics/Images/calibri.ttf"), al_map_rgba_f(1.0, 1.0, 1.0, 1.0), 20, 639, 29);
	gameScreen->addObject(hudText);
	hudTextTimer = new Timer(0.001);
	hudTextTimer->start();
	gameScreen->setVisible(true);
}

void GameGraphics::deleteGameScreen()
{
	delete board;
	delete hud;
	delete roof;
	delete hudTextTimer;
	delete textBox;
}

void GameGraphics::setBorderVisible(bool b)
{
	if (cont != nullptr)
		cont->setBorderVisible(b);
}

string GameGraphics::getPlayerName()
{
	if (current_screen = SETUP)
		return setupScreen->getPlayerName();
}

string GameGraphics::getIP()
{
	if (current_screen = IP)
		//return textBox->getText();
		return ipScreen->getIp();
	return "";
}
void GameGraphics::render()
{
	screen->draw();
	updateHudText();

}

void GameGraphics::update()
{
	if (current_screen == GAME)
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
	if(current_screen==GAME)
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

void GameGraphics::showDices(string message, vector<int> dices)
{
	dialogBox = new DialogBox(message, cont, true,DialogBox::MIDDLE, dices);
}

void GameGraphics::showAvailableLoots(string message, vector<lootType> dices)
{
	dialogBox = new DialogBox(message, cont, true, DialogBox::MIDDLE, dices);
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
	if (textBox != nullptr)
		return textBox->getPos() == pair<int, int>(CONSOLE_YPOS, CONSOLE_XPOS);
	else
		return false;
}

bool GameGraphics::writingInConsole()
{
	if (textBox != nullptr)
		return textBox->isClicked();
	else
		return false;
}

string GameGraphics::getConsoleText()
{
	if (current_screen == GAME && textBox != nullptr)
		return textBox->getText();
	return "";
}

void GameGraphics::printInHud(string s)
{
	// If time since last message is greater than minimum update text
	if (hudTextTimer->getCount() >= 1500 && hudTextQueue.empty())
	{
		hudText->setText(s);
		hudTextTimer->setCount(0);
	}
	// If not add it to the queue
	else
		hudTextQueue.push(s);
}

void GameGraphics::updateHudText()
{
	if (current_screen == GAME)
	{
		if (hudTextTimer->getCount() >= 1500 && hudTextQueue.empty() == false)
		{
			hudText->setText(hudTextQueue.front());
			hudTextQueue.pop();
			hudTextTimer->setCount(0);
		}
	}
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
	for (auto& s : screens)
		delete s;


	// FALTAN COSAS

}
