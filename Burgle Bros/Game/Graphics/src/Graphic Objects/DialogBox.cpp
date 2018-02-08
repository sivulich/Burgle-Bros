#include "DialogBox.h"

DialogBox::DialogBox(type t, std::string content, Container * c, bool bl, int position, vector<int>& d)
{
	int yOffset = 0;
	if (position == TOP)
		yOffset = -200;
	if (position == BOTTOM)
		yOffset = 200;


	box = new Container(string("./Graphics/Images/Dialog Box/box.png"));
	box->setPosition(yOffset + 290, 348);
	box->setScale(1);
	if (bl)
		blur = new Image(string("./Graphics/Images/blur.png"), 0, 0);
	else blur = nullptr;


	string font = string("./Graphics/Images/calibri.ttf");

	message = new Text(font, content, al_map_rgba_f(1, 1, 1, 0.5), 15, 640-348, 51);
	box->addObject(message);
	dices = new Container(50, 50 * 6 + 10 * 5, "Dice container");
	dices->setVisible(false);
	dices->setScale(0.8);
	

	parent = c;
	switch (t)
	{
	case OK_MSG:
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 237,  91);
		button1->setName(string("OK"));
		
		text1 = new Text(font, string("OK"), al_map_rgba_f(1, 1, 1, 1), 15, 640-348,  385-290);
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
		button1->setName(string("CANCEL"));
		text1 = new Text(font, string("CANCEL"), al_map_rgba_f(1, 1, 1, 1), 15, 640-348,  51);
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
	case DICE_MSG:
		
		for (unsigned i = 0; i < d.size(); i++)
		{
			Image* die = new Image("./Graphics/Images/Dices/White " + to_string(d[i]) + ".png");
			die->setPosition(0, dices->getWidth() / 6 * i);
			die->setScale(50.0 / die->getHeight());
			die->setClickable(false);
			dices->addObject(die);
		}
		dices->setClickable(false);
		dices->setVisible(true);
		dices->setPosition(box->getHeight() / 2 - dices->getHeight()*dices->getScale()*0.5,
			box->getWidth() / 2 - dices->getWidth()*dices->getScale()*d.size() / 12.0);
		message->setPosition(20, 640 - 348);
		box->addObject(dices);
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"));
		button1->setPosition(box->getHeight()*0.9 - button1->getHeight(), box->getWidth()*0.5 - button1->getWidth() / 2);
		button1->setName(string("OK"));

		text1 = new Text(font, string("OK"), al_map_rgba_f(1, 1, 1, 1), 15, 640 - 348, 385 - 290);
		text1->setPosition(box->getHeight()*0.9 - button1->getHeight() + 5, box->getWidth()*0.5 - text1->getWidth() / 2 );
		box->addObject(button1);
		box->addObject(text1);
		button2 = nullptr;
		text2 = nullptr;

		break;
	}
	parent->addObject(this);
}

void DialogBox::draw(Bitmap* target)
{
	if (blur != nullptr)
		blur->draw(target);

	box->draw(target);
	/*message->draw(target);
	if (button1 != nullptr)
	{
		button1->draw(target);
		text1->draw(target);
	}
	if (button2 != nullptr)
	{
		button2->draw(target);
		text2->draw(target);
	}*/
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