#include "Screen.h"

Screen::Screen(int h, int w, string& pathToBackground)
{
	initOk = false;
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
	if (background.get() != nullptr)
	{
		if (toDraw != nullptr && toDraw->get() != nullptr)
		{
			if (display != nullptr && display->get() != nullptr)
			{
				DEBUG_MSG_V("Correctly initialized screen with background " << pathToBackground);
				initOk = true;
			}
			else
				DEBUG_MSG("Couldnt create Display for screen");
		}
		else
			DEBUG_MSG("Couldnt create toDraw in screen");
	}
	else
		DEBUG_MSG("Couldnt load background " << pathToBackground);
}
string
Screen::click(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to click screen when it was not initialized correctly");
		return "";
	}
	DEBUG_MSG_V("Clicking on screen ");
	for (auto& ob : objects)
	{
		if (ob->overYou(y, x ) == true)
			return ob->click(y, x);
	}
	return "";
}

void
Screen::unClick(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to unclick screen when its not initialized correctly");
		return;
	}
	DEBUG_MSG_V("Unclicking screen");
	for (auto& ob : objects)
		ob->unClick(y,x);
}

void
Screen::draw()
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to draw screen when its not initialized correctly");
		return;
	}
	DEBUG_MSG_V("Drawing screen");
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
	if (initOk == false)
	{
		DEBUG_MSG("Trying to hover screen when it was not initialized correctly");
		return false;
	}
	DEBUG_MSG_V("Hovering on screen");
	for (auto& ob:objects)
		ob->overYou(y, x);
	return true;
}
void
Screen::drag(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to drag on screen when it was not initialized correctly");
		return ;
	}
	DEBUG_MSG_V("Draging on screen");
	for (auto& ob : objects)
		if(ob->overYou(y,x)==true)
			ob->drag(y, x);
}