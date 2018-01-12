#include "DialogBox.h"

DialogBox::DialogBox(type t, std::string content, Container * c)
{
	box = new Image(string("./Graphics/Images/Dialog Box/box.png"), 348, 290);
	blur = new Image(string("./Graphics/Images/blur.png"), 0, 0);
	string font = string("./Graphics/Images/calibri.ttf");

	message = new Text(font, content, al_map_rgba_f(1, 1, 1, 0.5), 15, 640, 290 + 51);
	parent = c;
	switch (t)
	{
	case OK_MSG:
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 348 + 237, 290 + 91);
		button1->setName(string("OK"));
		text1 = new Text(font, string("OK"), al_map_rgba_f(1, 1, 1, 1), 15, 640, 385);
		button2 = nullptr;
		text2 = nullptr;
		break;
	case YES_NO_MSG:
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 348 + 98, 290 + 91);
		button1->setName(string("NO"));
		button2 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 348 + 375, 290 + 91);
		button2->setName(string("YES"));
		text1 = new Text(font, string("NO"), al_map_rgba_f(1, 1, 1, 1), 15, 500, 385);
		text2 = new Text(font, string("YES"), al_map_rgba_f(1, 1, 1, 1), 15, 778, 385);
		break;
	case CANCEL_MSG:
		button1 = new Image(string("./Graphics/Images/Dialog Box/button.png"), 348 + 237, 290 + 91);
		button1->setName(string("CANCEL"));
		text1 = new Text(font, string("CANCEL"), al_map_rgba_f(1, 1, 1, 1), 15, 640, 290 + 51);
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
	parent->addObject(this);
}

void DialogBox::draw(Bitmap* target)
{
	blur->draw(target);
	box->draw(target);
	message->draw(target);
	if (button1 != nullptr)
	{
		button1->draw(target);
		text1->draw(target);
	}
	if (button2 != nullptr)
	{
		button2->draw(target);
		text2->draw(target);
	}
}

std::string DialogBox::click(int y, int x)
{
	string b1 = "";
	if (button1 != nullptr)
		b1 = button1->click(y, x);

	string b2 = "";
	if (button2 != nullptr)
		b2 = button2->click(y, x);

	if (b1 != "" || b2 != "")
	{
		parent->removeObject(this);
		delete this;
		return b1 != "" ? b1 : b2;
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