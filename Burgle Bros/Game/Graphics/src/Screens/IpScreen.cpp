#include "IpScreen.h"

IpScreen::IpScreen(Container* p) :Container(SCREEN_HEIGHT, SCREEN_WIDTH, "IP_SCREEN")
{
	setPosition(0, 0);
	p->addObject(this);
	setBackground(string("./Graphics/Images/Screen - Mode/backgroundIP.jpg"));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/CONNECT.png"), 399, 389));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/BACK.png"), 0, 617));
	addObject(new Image(string("./Graphics/Images/Screen - Mode/EXIT.png"), 1134, 631));

	textBox = new Textbox(537, 325, 260, 44, string("./Graphics/Images/arial_narrow.ttf"));
	textBox->setMax(16);
	textBox->setText(string("127.0.0.1"));
	textBox->setFontColor(al_map_rgba_f(1, 1, 1, 0.5));
	textBox->setBoxColor(al_map_rgba_f(0, 0, 0, 0));
	addObject(textBox);
	setVisible(false);
}

string
IpScreen::getIp()
{
	return textBox->getText();
}
IpScreen::~IpScreen()
{
}