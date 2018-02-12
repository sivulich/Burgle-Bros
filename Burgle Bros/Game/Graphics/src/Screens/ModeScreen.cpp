#include "ModeScreen.h"

ModeScreen::ModeScreen(Container* p) : Container(SCREEN_HEIGHT, SCREEN_WIDTH, "MODE_SCREEN")
{
	setPosition(0, 0);
	p->addObject(this);
	setBackground(string("./Graphics/Images/Screen - Mode/background.jpg"));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/LOCAL.png")));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/REMOTE.png")));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/BACK.png"), 0, 617));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/EXIT.png"), 1134, 631));
	setVisible(false);
}