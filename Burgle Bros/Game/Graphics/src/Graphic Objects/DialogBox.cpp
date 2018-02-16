#include "DialogBox.h"

DialogBox::DialogBox(type t, std::string content, Container * c, bool bl, int position)
{
	int yOffset = 0;
	if (position == TOP)
		yOffset = -200;
	if (position == BOTTOM)
		yOffset = 200;


	box = new Container(string("./Graphics/Images/Dialog Box/box.png"));
	box->setScale(1);
	box->setPosition(c->getHeight() / 2 - box->getHeight()*box->getScale()*0.5,
		c->getWidth() / 2 - box->getWidth()*box->getScale()*0.5);
	if (bl)
		blur = new Image(string("./Graphics/Images/blur.png"), 0, 0);
	else blur = nullptr;


	string font = string("./Graphics/Images/calibri.ttf");
	unsigned lines = ceil(content.size()*1.0 / 80.0);
	for (unsigned i = 0; i < lines - 1; i++)
	{
		message = new Text(font, content.substr(i * 80, 80), al_map_rgba_f(1, 1, 1, 0.5), 15, box->getWidth() / 2 , 51 - (9.0*lines) + 18.0*i);
		box->addObject(message);
	}
	message = new Text(font, content.substr((lines-1) * 80), al_map_rgba_f(1, 1, 1, 0.5), 15, box->getWidth() / 2 , 51 - (9.0*lines) + 18.0*(lines - 1));
	box->addObject(message);

	parent = c;
	switch (t)
	{
	case OK_MSG:
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 237,  91);
		button1->setPosition(91, box->getWidth() / 2 - button1->getWidth() / 2);
		button1->setName(string("OK"));
		
		text1 = new Text(font, string("OK"), al_map_rgba_f(1, 1, 1, 1), 15, box->getWidth()/2,  95);
		box->addObject(button1);
		box->addObject(text1);
		button2 = nullptr;
		text2 = nullptr;
		break;
	case YES_NO_MSG:
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 98,  91);
		button1->setName(string("NO"));
		button2 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 375, 91);
		button2->setName(string("YES"));
		
		text1 = new Text(font, string("NO"), al_map_rgba_f(1, 1, 1, 1), 15, 500-348, 385-290);
		text2 = new Text(font, string("YES"), al_map_rgba_f(1, 1, 1, 1), 15, 778-348,  385-290);
		box->addObject(button1);
		box->addObject(button2);
		box->addObject(text1);
		box->addObject(text2);
		break;
	case CANCEL_MSG:
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"),  237,  91);
		button1->setPosition(91, box->getWidth() / 2 - button1->getWidth() / 2);
		button1->setName(string("CANCEL"));
		text1 = new Text(font, string("CANCEL"), al_map_rgba_f(1, 1, 1, 1), 15, box->getWidth()/2,  51);
		box->addObject(button1);
		box->addObject(text1);
		button2 = nullptr;
		text2 = nullptr;
		break;

	case TEMPORAL_INFO:
		button1 = nullptr;
		text1 = nullptr;
		button2 = nullptr;
		text2 = nullptr;
		break;
	}
	if (text1 != nullptr)
	{
		text1->setClickable(false);
		text1->setHoverable(false);
	}
	if (text2 != nullptr)
	{
		text2->setClickable(false);
		text2->setHoverable(false);
	}
	parent->addObject(this);
}
DialogBox::DialogBox(std::string content, Container * c, bool bl, int position, vector<int>& d)
{
	parent = c;
	int yOffset = 0;
	if (position == TOP)
		yOffset = -200;
	if (position == BOTTOM)
		yOffset = 200;

	diceBox = true;
	box = new Container(string("./Graphics/Images/Dialog Box/box.png"));
	box->setScale(1);
	box->setPosition(c->getHeight() / 2 - box->getHeight()*box->getScale()*0.5,
		c->getWidth() / 2 - box->getWidth()*box->getScale()*0.5);
	if (bl)
		blur = new Image(string("./Graphics/Images/blur.png"), 0, 0);
	else blur = nullptr;


	string font = string("./Graphics/Images/calibri.ttf");

	message = new Text(font, content, al_map_rgba_f(1, 1, 1, 0.5), 15, box->getWidth()/2, 51);
	box->addObject(message);
	dices = new Container(50, 50 * d.size() + 10 * (d.size()-1), "Dice container");
	dices->setVisible(false);
	for (unsigned i = 0; i < d.size(); i++)
	{
		Image* die = new Image("./Graphics/Images/Dices/White " + to_string(d[i]) + ".png");
		die->setPosition(0, dices->getWidth()*1.0 / d.size() * i);
		die->setScale(50.0 / die->getHeight());
		die->setClickable(false);
		dices->addObject(die);
	}
	dices->setClickable(false);
	dices->setVisible(true);
	dices->setPosition(box->getHeight() / 2 - dices->getHeight()*dices->getScale()*0.5,
		box->getWidth() / 2 - dices->getWidth()*dices->getScale()*0.5);
	message->setPosition(20, box->getWidth() / 2);
	box->addObject(dices);
	button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"));
	button1->setPosition(box->getHeight()*0.9 - button1->getHeight(), box->getWidth()*0.5 - button1->getWidth() / 2);
	button1->setName(string("OK"));

	text1 = new Text(font, string("OK"), al_map_rgba_f(1, 1, 1, 1), 15, 640 - 348, 385 - 290);
	text1->setPosition(box->getHeight()*0.9 - button1->getHeight() + 5, box->getWidth()*0.5 );
	box->addObject(button1);
	box->addObject(text1);
	button2 = nullptr;
	text2 = nullptr;
	parent->addObject(this);
	dice = new alx::Sample("../Game/Sound/DICES.wav");
	if (text1 != nullptr)
	{
		text1->setClickable(false);
		text1->setHoverable(false);
	}
	if (text2 != nullptr)
	{
		text2->setClickable(false);
		text2->setHoverable(false);
	}
}
DialogBox::DialogBox(std::string content, Container * c, bool bl, int position, vector<lootType>& d)
{
	parent = c;
	int yOffset = 0;
	if (position == TOP)
		yOffset = -200;
	if (position == BOTTOM)
		yOffset = 200;


	box = new Container(string("./Graphics/Images/Dialog Box/LootBox.png"));
	
	box->setScale(1);
	box->setPosition(c->getHeight()/2-box->getHeight()*box->getScale()*0.5,
		             c->getWidth() / 2 - box->getWidth()*box->getScale()*0.5);
	if (bl)
		blur = new Image(string("./Graphics/Images/blur.png"), 0, 0);
	else blur = nullptr;


	string font = string("./Graphics/Images/calibri.ttf");

	message = new Text(font, content, al_map_rgba_f(1, 1, 1, 0.5), 15, box->getWidth()/2, 20);
	box->addObject(message);
	for (unsigned i = 0; i < d.size(); i++)
	{
		Image* die = new Image("./Graphics/Images/Loot/" + string(toString(d[i])) + ".png");

		die->setPosition(90, (145+12) * i+62);
		die->setScale(145.0 / die->getHeight());
		die->setClickable(true);
		box->addObject(die);
	}
	message->setPosition(20, box->getWidth()/2);
	button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 237, 265);
	button1->setPosition(265, box->getWidth()/2-button1->getWidth()/2);
	button1->setName(string("CANCEL"));

	text1 = new Text(font, string("CANCEL"), al_map_rgba_f(1, 1, 1, 1), 15, box->getWidth()/2, 265+5);
	box->addObject(button1);
	box->addObject(text1);
	parent->addObject(this);
	if (text1 != nullptr)
	{
		text1->setClickable(false);
		text1->setHoverable(false);
	}
	if (text2 != nullptr)
	{
		text2->setClickable(false);
		text2->setHoverable(false);
	}
}

void DialogBox::draw(Bitmap* target)
{
	if (blur != nullptr)
		blur->draw(target);
	if (diceBox==true && played == false && (played = true) == true)
		dice->play(1, 0, 1, ALLEGRO_PLAYMODE_ONCE);
	box->draw(target);
}

std::string DialogBox::click(int y, int x)
{
	string b1 = box->click(y, x);

	if (b1 != "" && b1!="box")
	{
		parent->removeObject(this);
		delete this;
		return b1;
	}
	return string("");
}

void DialogBox::unClick(int y, int x)
{
	if (button1 != nullptr)
		button1->unClick(y, x);
	if (button2 != nullptr)
		button2->unClick(y, x);
}
bool DialogBox::overYou(int y, int x)
{
	if (button1 != nullptr)
		button1->overYou(y, x);
	if (button2 != nullptr)
		button2->overYou(y, x);
	return true;
}

void DialogBox::remove()
{
	parent->removeObject(this);
	delete this;
}