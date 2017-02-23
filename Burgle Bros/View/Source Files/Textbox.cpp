#include "Textbox.h"
#include <ctype.h>

Textbox::Textbox(int y, int x, string& path, int fSize,int max)
{
	font = new Font(path.c_str(), fSize, 0);
	int point = path.find('.');
	name = path.substr(0, point)+"-size:" + to_string(fSize) + "pos" + to_string(y) + ":" + to_string(x);
	this->y = y;
	this->x = x;
	this->size = max;
	w =10+size* font->getWidth("W");
	h = 4 + font->getHeight();
	scale = 1;
	titilate = new Timer(0.5);
	queue << Keyboard::getEventSource();
	fitToBox = false;
	if (titilate != nullptr)
	{
		if (font != nullptr && font->get() != nullptr)
		{
			DEBUG_MSG_V("Correctly initialized textbox " << name);
			initOk = true;
		}
		else
			DEBUG_MSG("Error loading font for textbox " << name);
	}
	else
		DEBUG_MSG("Error creating timer for textbox " << name);

}
string
Textbox::click(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to click on " << name << " that is no initialized correctly");
		return "";
	}

	if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		DEBUG_MSG_V("Clicking textbox " << name);
		clicked = true;
		titilate->start();
		return name;
	}
	return "";
}

void
Textbox::unClick(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to unclick on " << name << " that is no initialized correctly");
		return ;
	}
	
	if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
		return;
	DEBUG_MSG_V("Unclicking textbox " << name);
	clicked = false;
	titilate->stop();
	return;
}
bool
Textbox::overYou(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to hover on " << name << " that is no initialized correctly");
		return false;
	}
	if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		DEBUG_MSG_V("Hovering textbox " << name);
		hover = true;
		return true;
	}
	hover = false;
	return false;
}
void
Textbox::draw(Bitmap* target)
{
	if (initOk == true && target != nullptr && target->get() != nullptr)
		target->setTarget();
	else if (initOk == true)
	{
		DEBUG_MSG("Error while drawing textbox " << name << " target was not initialized correctly");
		return;
	}
	else
	{
		DEBUG_MSG("Trying to draw textbox when it was not initialized");
		return;
	}
	DEBUG_MSG_V("Drawing textbox " << name);
	al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(255, 255, 255));
	if (clicked == true && queue.isEmpty() == false)
	{
		event = queue.getEvent();
		
		if (event.getType() == ALLEGRO_EVENT_KEY_CHAR)
		{
			int c = event.getKeyboardCharacter();
			if (event.getKeyboardKeycode() == ALLEGRO_KEY_BACKSPACE && buffer.size() > 0)
				buffer.pop_back();
			else if (isascii(c) &&  (  font->getWidth(buffer.c_str())+font->getWidth("W") <= w-10 && ( fitToBox==true ? true : buffer.size() < size)))
					buffer.push_back(c);
			
				
		}
	}
	font->draw(x + 5, y + 2, al_map_rgb(0, 0, 0), buffer.c_str());
	if(clicked==true && titilate->getCount()%2==0)
		al_draw_line(x + font->getHeight()/5+ font->getWidth(buffer.c_str() ), y + 2, x + font->getHeight() / 5 + font->getWidth(buffer.c_str()), y + 2 + font->getHeight(), al_map_rgb(0, 0, 0), 2);
}