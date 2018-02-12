#include "MenuScreen.h"

MenuScreen::MenuScreen(Container* p) : Container(SCREEN_HEIGHT, SCREEN_WIDTH, "MENU_SCREEN")
{
	setPosition(0, 0);
	p->addObject(this);
	setBackground(string("./Graphics/Images/Menu/background.jpg"));

	addObject(new Button(string("START"),
		string("./Graphics/Images/Menu/start.png"),
		string("./Graphics/Images/Menu/startHover.png"),
		string("./Graphics/Images/Menu/startClicked.png")));
	addObject(new Button(string("CREDITS"),
		string("./Graphics/Images/Menu/credits.png"),
		string("./Graphics/Images/Menu/creditsHover.png"),
		string("./Graphics/Images/Menu/creditsClicked.png")));
	addObject(new Button(string("RULES"),
		string("./Graphics/Images/Menu/rules.png"),
		string("./Graphics/Images/Menu/rulesHover.png"),
		string("./Graphics/Images/Menu/rulesClicked.png")));
	addObject(new Button(string("EXIT"),
		string("./Graphics/Images/Menu/exit.png"),
		string("./Graphics/Images/Menu/exitHover.png"),
		string("./Graphics/Images/Menu/exitClicked.png")));
}