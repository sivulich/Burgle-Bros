#include "SetupScreen.h"

SetupScreen::SetupScreen(Container* p) : Container(SCREEN_HEIGHT, SCREEN_WIDTH, "SETUP_SCREEN")
{
	p->addObject(this);
	setPosition(0, 0);
	Image*i;
	setBackground(string("./Graphics/Images/Setup/background.jpg"));
	addObject(new Image(string("./Graphics/Images/Setup/BACK.png"), 0, 616));
	addObject(new Image(string("./Graphics/Images/Setup/NEXT.png"), 1136, 632));
	addObject(new Image(string("./Graphics/Images/Setup/ACROBAT.png"), 53, 311));
	addObject(new Image(string("./Graphics/Images/Setup/SPOTTER.png"), 147, 286));
	addObject(new Image(string("./Graphics/Images/Setup/JUICER.png"), 254, 260));
	addObject(new Image(string("./Graphics/Images/Setup/HAWK.png"), 361, 236));
	i = new Image(string("./Graphics/Images/Setup/ROOK.png"), 463, 184);
	i->disable();
	addObject(i);
	addObject(new Image(string("./Graphics/Images/Setup/HACKER.png"), 597, 190));
	addObject(new Image(string("./Graphics/Images/Setup/RAVEN.png"), 714, 234));
	i = new Image(string("./Graphics/Images/Setup/RIGGER.png"), 880, 247);
	i->disable();
	addObject(i);
	addObject(new Image(string("./Graphics/Images/Setup/PETERMAN.png"), 1073, 311));

	// Load the textbox to enter the players name
	textBox = new Textbox(574, 645, 270, 44, string("./Graphics/Images/arial_narrow.ttf"));
	textBox->setFontColor(al_map_rgba_f(1, 1, 1, 0.5));
	textBox->setBoxColor(al_map_rgba_f(0, 0, 0, 0));
	addObject(textBox);
	// Load player number
    player1 =new Image(string("./Graphics/Images/Setup/PLAYER1.png"), 592, 120);
	player1->setVisible(false);
	player1->setHoverable(false);
	player1->setClickable(false);
	player2 =new Image(string("./Graphics/Images/Setup/PLAYER2.png"), 592, 120);
	player2->setVisible(false);
	player2->setHoverable(false);
	player2->setClickable(false);
	addObject(player1);
	addObject(player2);
}

string SetupScreen::click(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to click container " << name << " when it was not initialized correctly");
		return "";
	}
	DEBUG_MSG_V("Clicking on container " << name);

	if (clickable == true && isInside(y, x) && visible == true)
	{
		string s = "";
		if (onlyClickMe == false)
		{
			for (auto& ob : objects)
			{
				if (ob->overYou((y - this->y) / scaleY, (x - this->x) / scaleX) == true)
				{
					s = ob->click((y - this->y) / scaleY, (x - this->x) / scaleX);
					if (s == string("Not Clickable"))
						continue;
					else
					{
						//cout << isInEnum_characterType(ob->getName().c_str()) << endl;
						if (isInEnum_characterType(ob->getName().c_str()))
						{
							for (auto& obj : objects)
									((Image*)obj)->setTone(1, 1, 1);
							((Image*)ob)->setTone(1, 0.5, 0.5);
							return s;
						}
					}

				}
					
			}
			return s;
		}
		else
		{
			clicked = true;

			if (dontClickMe == false)
				return name;
			else
				return "";
		}

	}
	return "";
}

void SetupScreen::reset()
{
	for (auto& obj : objects)
	{
		if (obj->getName() != "ROOK" && obj->getName() != "RIGGER")
			obj->enable();
		((Image*)obj)->setTone(1, 1, 1);
	}
	textBox->clear();
}
void SetupScreen::showPlayer1()
{
	reset();		
	player1->setVisible(true);
	player2->setVisible(false);
};

void SetupScreen::showPlayer2(string& character)
{
	reset();
	disableChild(character);
	player1->setVisible(false);
	player2->setVisible(true);	
};
