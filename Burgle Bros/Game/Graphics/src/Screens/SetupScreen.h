#pragma once
#include "Container.h"
#include "Image.h"
#include "../../include/GraphicsDefs.h"
#include "Textbox.h"

class SetupScreen : public Container
{
public:
	SetupScreen(Container* p);
	void showPlayer1() { for(auto& obj:objects) obj->enable(); player1->setVisible(true); };
	string click(int y, int x)override;
	void showPlayer2(string& character) { player1->setVisible(false); player2->setVisible(true); textBox->clear(); disableChild(character); };
	string getPlayerName() { return textBox->getText(); };
private:
	Textbox* textBox;
	Image* player1, *player2;
};
