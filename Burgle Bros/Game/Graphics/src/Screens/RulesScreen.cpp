#include "RulesScreen.h"

RulesScreen::RulesScreen(Container* p) :Container(SCREEN_HEIGHT, SCREEN_WIDTH, "RULES_SCREEN")
{
	p->addObject(this);
	setPosition(0, 0);
	setBackground(string("./Graphics/Images/Screen - Mode/background.jpg"));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/BACK.png")));
	setVisible(false);
}