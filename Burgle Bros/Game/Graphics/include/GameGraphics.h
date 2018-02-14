#pragma once
#include <GameModel.h>
#include <GraphicsDefs.h>
#include <alx.hpp>
#include "Button.h"
#include "Animations.h"
#include "../../Sound/SoundEffects.h"
//Screens
#include "../src/Screens/IpScreen.h"
#include "../src/Screens/ModeScreen.h"
#include "../src/Screens/MenuScreen.h"
#include "../src/Screens/CreditScreen.h"
#include "../src/Screens/SetupScreen.h"
#include "../src/Screens/RulesScreen.h"

#include "../Graphic Objects/Screen.h"
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Textbox.h"
#include "../Graphic Objects/DialogBox.h"
#include "../Observers/Observer.h"
#include "../Observers/BoardObserver.h"
#include "../Observers/HudObserver.h"


class GameGraphics : public Observer
{
public:
	GameGraphics(GameModel * model=nullptr);

	// Set new model to the view
	void setModel(GameModel * m);
	~GameGraphics();

	// Check Allegro initialization
	bool initOK() { return initOK_; };

	// Render objects on screen
	void render();

	// Called by Game Model when something is modified
	//IMPLEMENTAR
	void update();

	// Interacts upon a mouse movement, returns objet name
	bool hover(int y, int x);

	// Interacts upon a click down, returns objet name
	string click(int y, int x);

	// Interacts upon a click up, returns objet name
	void unclick(int y, int x);

	// Pop up a message to answer YES or NO
	void askQuestion(string question);

	// Pop up a message to answer OK
	void showOkMessage(string message);

	// Pop up a message showing dices
	void showDices(string message, vector<int> dices);
	
	//Pop up a message showing aveilable loots
	void showAvailableLoots(string message, vector<lootType> dices);
		//
	void showCancelMessage(string message);

	// Show temp message, must call 'removeDialogBox' 
	void showTempMessage(string message);

	// Show top of the patrol  deck
	void showTopPatrol(int floorNumber) { board->showTopPatrol(floorNumber); };
	// Hide top of the patrol deck
	void hideTopPatrol(int floorNumber) { board->hideTopPatrol(floorNumber); }
	// Ask the player confirmation and shows the top of the deck
	void spyPatrolCard(int floorNumber);

	// Zoom the clicked tile
	void zoomTile(Coord c);
	// Unzoom the tile
	void unZoomTile();

	// If dialog box is set with no buttons, removes it
	void removeDialogBox();

	// When answered, call this function
	void closeQuestion();

	// Set as clickable the given tiles (and illuminate them), and not clickable the other ones.
	void setTilesClickable(vector<Coord> tiles);

	// Set as clickable all the tiles
	void setAllClickable();

	// Set visible the border of all grafic objects
	void setBorderVisible(bool b);

	// Return screen event source (for controller)
	EventSource getScreenEventSource() { return screen->getDisplay()->getEventSource(); }

	// Return true if guard is moving
	bool guardIsMoving() { if (current_screen = GAME) return board->guardIsMoving(); };
	// Create graphic objects to represent game model on scren


	//
	void showMenuScreen();
	//
	void showCreditsScreen();
	//
	void showRulesScreen();
	//
	void showModeScreen();

	void showIPScreen();

	void showSetupScreen(int player = 0);
	// Shows the game screen
	void showGameScreen();
	void deleteGameScreen();

	//
	void showPauseScreen();
	void hidePauseScreen();

	// Show a console to input text
	void toggleConsole();
	void showConsole();
	void hideConsole();
	bool showingConsole();
	bool writingInConsole();
	string getConsoleText();

	//
	void printInHud(string s);

	// In setup screen get players name
	string getPlayerName();
	// In IP screen get IP
	string getIP();
private:
	bool initOK_;

	typedef enum { MENU, RULES, CREDITS, MODE, SETUP, IP, GAME } SCREEN;
	SCREEN current_screen;
	//Sound
	SoundEffects sound;
	// Pointer to the Game Model
	GameModel * model;

	// Graphic objects
	Screen* screen;
	Container* cont;
	Image * roof;

	//Screens
	void setAllNotVisible() { for (auto& s : screens)s->setVisible(false); };
	vector<Object*> screens;
	IpScreen* ipScreen;
	ModeScreen* modeScreen;
	MenuScreen* menuScreen;
	CreditScreen* creditScreen;
	SetupScreen* setupScreen;
	RulesScreen* rulesScreen;
	Container* gameScreen;

	
	Textbox * textBox;
	Timer * hudTextTimer;
	queue<string> hudTextQueue;
	Text* hudText;
	DialogBox * dialogBox;
	Image * blur;


	// Observers
	BoardObserver* board;
	HudObserver * hud;

	void updateHudText();

};

