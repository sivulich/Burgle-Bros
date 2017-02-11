
#include "Container.h"

Container::Container(ALLEGRO_BITMAP* b)
{
	background = b;
	toDraw = b;
	h = al_get_bitmap_height(b);
	w = al_get_bitmap_width(b);
	offsetX = offsetY = 0;
	bScale = 1;
}
Container::Container(int h, int w)
{
	this->h = h;
	this->w = w;
	offsetX = offsetY = 0;
	bScale = 1;
	toDraw = al_create_bitmap(w, h);
}

void
Container::draw(ALLEGRO_BITMAP* target)
{
	al_set_target_bitmap(toDraw);
	al_draw_bitmap(background, offsetX, offsetY, 0);
	for (auto & x : objects)
		x->draw(toDraw);
	al_set_target_bitmap(target);
	al_draw_scaled_bitmap(toDraw, 0, 0, w, h, x, y, scale*w, scale*h, 0);
}

string
Container::click(int y, int x)
{
	if (this->x <= x  &&  x <= (this->x + this->w) && this->y <= y && y <= (this->y + this->h))
	{
		for (auto& ob : objects)
		{
			if (ob->overYou(y - this->y, x - this->x) == true)
				return ob->click(y, x);
		}
		if (clickable == true)
		{
			clicked = true;
			return name;
		}
	}
	return "";
}
void
Container::unClickAll()
{
	clicked = false;
	for (auto& x : objects)
		x->unClick();
}