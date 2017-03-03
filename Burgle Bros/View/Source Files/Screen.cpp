#include "../Header Files/Screen.h"

Screen::Screen(int h, int w, string& pathToBackground,bool b)
{
	initOk = false;
	if (b == true)
	{
		ALLEGRO_DISPLAY_MODE   disp_data;
		al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
		display = new Display(disp_data.width, disp_data.height);
		display->setFlagEnabled(ALLEGRO_FULLSCREEN_WINDOW,false);
		this->w = disp_data.width;
		this->h = disp_data.height;
	}
	else
	{
		this->h = h;
		this->w = w;
	}
	display = new Display(this->w, this->h);
	toDraw = new Bitmap(this->w, this->h);
	
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