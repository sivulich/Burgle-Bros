#include "Textbox.h"
#include <ctype.h>

Textbox::Textbox(int y, int x, string& path, int fSize,int max)
{
	al_init(); //ESTO ES RE CABEZA DESPUES CAMBIEMOSLOOO
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	font = new Font(path.c_str(), fSize, 0);
	int point = path.find('.');
	name = path.substr(0, point)+"-size:" + to_string(fSize) + "pos" + to_string(y) + ":" + to_string(x);
	this->y = y;
	this->x = x;
	this->size = max;
	w =10+size* font->getWidth("H");
	h = 4 + font->getHeight();
	scale = 1;
	titilate = new Timer(0.5);
	queue << Keyboard::getEventSource();
	fitToBox = false;
}
string
Textbox::click(int y, int x)
{
	if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		clicked = true;
		titilate->start();
		return name;
	}
	return "";
}

void
Textbox::unClick(int y, int x)
{
	if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
		return;
	clicked = false;
	titilate->stop();
	return;
}
void
Textbox::draw(Bitmap* target)
{
	target->setTarget();
	al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(255, 255, 255));
	if (clicked == true && queue.isEmpty() == false)
	{
		event = queue.getEvent();
		
		if (event.getType() == ALLEGRO_EVENT_KEY_CHAR)
		{
			int c = event.getKeyboardCharacter();
			if (event.getKeyboardKeycode() == ALLEGRO_KEY_BACKSPACE && buffer.size() > 0)
				buffer.pop_back();
			else if (isascii(c) &&  ( x + font->getWidth(buffer.c_str()) < x+w && ( fitToBox==true ? true : buffer.size() < size)))
					buffer.push_back(c);
			
				
		}
	}
	else queue.clear();

	font->draw(x + 5, y + 2, al_map_rgb(0, 0, 0), buffer.c_str());
	if(clicked==true && titilate->getCount()%2==0)
		al_draw_line(x + 10 + font->getWidth(buffer.c_str()), y + 2, x + 10 + font->getWidth(buffer.c_str()), y + 2 + font->getHeight(), al_map_rgb(0, 0, 0), 2);
}