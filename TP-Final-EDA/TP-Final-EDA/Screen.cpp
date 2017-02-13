#include "Screen.h"

Screen::Screen(int h, int w, string& pathToBackground)
{
	initOk = false;
	if (al_init() == true)
	{
		if (al_init_image_addon()==true && al_init_primitives_addon()==true )
		{
			display = new Display(w, h);
			toDraw = new Bitmap(w, h);
			this->h = h;
			this->w = w;
			clickable = false;
			hoverable = false;
			offsetX = 0;
			offsetY = 0;
			bScale = 1;
			background.load(pathToBackground.c_str());
			initOk = true;
		}
		else
			cout << "Couldnt init allegro addons" << endl;
	}
	else
		cout << "Couldnt init allegro" << endl;
}
string
Screen::click(int y, int x)
{
	for (auto& ob : objects)
	{
		if (ob->overYou(y, x ) == true)
			return ob->click(y, x);
	}
	return "";
}

void
Screen::unClick()
{
	for (auto& ob : objects)
		ob->unClick();
}

void
Screen::draw()
{
	toDraw->setTarget();
	background.drawScaled( offsetX, offsetY, background.getWidth(), background.getHeight(), 0, 0,
		bScale*background.getWidth(), bScale* background.getHeight(), 0);
	for (int i = objects.size() - 1; i >= 0; i--)
		objects[i]->draw(toDraw);
	display->setTarget(*display);
	toDraw->draw(0, 0, 0);
	al_flip_display();
}

bool
Screen::overYou(int y, int x)
{
	for (int i = objects.size() - 1; i >= 0; i--)
		objects[i]->overYou(y, x);
	return true;
}