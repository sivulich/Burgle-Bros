#pragma once
#include "Container.h"
#include "Image.h"
#include "../../include/GraphicsDefs.h"
#include "Textbox.h"

class SetupScreen : public Container
{
public:
	SetupScreen(Container* p);
	void reset();
	void showPlayer1();
	void showPlayer2(string& character);
	string click(int y, int x)override;
	string getPlayerName() { return textBox->getText(); };
private:
	Textbox* textBox;
	Image* player1, *player2;
};
