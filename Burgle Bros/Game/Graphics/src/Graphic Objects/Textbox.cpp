#include "./Textbox.h"
#include <ctype.h>

Textbox::Textbox(int y, int x, string& path, int fSize, int max)
{
	font = new Font(path.c_str(), fSize, 0);
	int point = path.find('.');
	name = path.substr(0, point) + "-size:" + to_string(fSize) + "pos" + to_string(y) + ":" + to_string(x);
	this->y = y;
	this->x = x;
	this->size = max;
	w = 10 + size* font->getWidth("W");
	h = 4 + font->getHeight();
	titilate = new Timer(0.5);
	queue << Keyboard::getEventSource();
	fitToBox = false;
	curPos = 0;
	fontColor = al_map_rgba_f(0, 0, 0, 1);
	boxColor = al_map_rgba_f(1, 1, 1, 1);
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

Textbox::Textbox(int x, int y, int w, int h, string& path)
{
	font = new Font(path.c_str(), h - 4, 0);
	int point = path.find('.');
	name = path.substr(0, point) + "-size:" + to_string(h - 4) + "pos" + to_string(y) + ":" + to_string(x);
	this->y = y;
	this->x = x;
	this->w = w;
	this->h = h;
	titilate = new Timer(0.5);
	queue << Keyboard::getEventSource();
	fitToBox = true;
	curPos = 0;
	fontColor = al_map_rgba_f(0, 0, 0, 1);
	boxColor = al_map_rgba_f(1, 1, 1, 1);
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

void Textbox::setMax(int max)
{
	this->size = max;
}

string Textbox::click(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to click on " << name << " that is no initialized correctly");
		return "";
	}

	if (this->x <= x  &&  x <= (this->x + scaleX*this->w) && this->y <= y && y <= (this->y + scaleY*this->h))
	{
		DEBUG_MSG_V("Clicking textbox " << name);
		clicked = true;
		titilate->start();
		queue.clear();
		return name;
	}
	return "";
}

void Textbox::click()
{
	clicked = true;
	titilate->start();
	queue.clear();

}

void Textbox::unClick(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to unclick on " << name << " that is no initialized correctly");
		return;
	}

	if (this->x <= x  &&  x <= (this->x + scaleX*this->w) && this->y <= y && y <= (this->y + scaleY*this->h))
		return;
	DEBUG_MSG_V("Unclicking textbox " << name);
	clicked = false;
	titilate->stop();
	return;
}
void Textbox::unClick()
{
	clicked = false;
	titilate->stop();
}
bool Textbox::overYou(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to hover on " << name << " that is no initialized correctly");
		return false;
	}
	if (this->x <= x  &&  x <= (this->x + scaleX*this->w) && this->y <= y && y <= (this->y + scaleY*this->h))
	{
		DEBUG_MSG_V("Hovering textbox " << name);
		hover = true;
		return true;
	}
	hover = false;
	return false;
}
void Textbox::draw(Bitmap* target)
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
	
	playAnimation();
	
	if (visible)
	{
		if (clicked == true && queue.isEmpty() == false)
		{
			event = queue.getEvent();
			if (event.getType() == ALLEGRO_EVENT_KEY_CHAR)
			{
				if (isprint(event.getKeyboardCharacter()) && (font->getWidth(buffer.c_str()) + font->getWidth("W") <= w - 10 && (fitToBox == true ? true : buffer.size() < (unsigned)size)))
				{
					buffer.insert(curPos, 1, event.getKeyboardCharacter());
					curPos++;
				}
			}
			else if (event.getType() == ALLEGRO_EVENT_KEY_DOWN)
			{
				int c = event.getKeyboardKeycode();
				if (c == ALLEGRO_KEY_LEFT && curPos > 0)
					curPos--;

			else if (c == ALLEGRO_KEY_RIGHT && curPos < (long long)buffer.size())
				curPos++;

				else if (c == ALLEGRO_KEY_BACKSPACE && curPos > 0)
				{
					curPos--;
					buffer.erase(curPos, 1);
				}
			}
		}

		al_draw_filled_rectangle(x, y, x + w, y + h, boxColor);
		font->draw(x + 5, y + 2, fontColor, buffer.c_str());
		if (clicked == true && titilate->getCount() % 2 == 0)
			al_draw_line(x + font->getWidth(buffer.substr(0, curPos).c_str()) + 3, y, x + font->getWidth(buffer.substr(0, curPos).c_str()) + 3, y + font->getHeight(), fontColor, 2);
	}

}

string Textbox::getText()
{
	return buffer;
}