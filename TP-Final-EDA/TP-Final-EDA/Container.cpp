
#include "Container.h"

Container::Container(string& path)
{
	background = al_load_bitmap(path.c_str());
	toDraw = background;
	h = al_get_bitmap_height(background);
	w = al_get_bitmap_width(background);
	offsetX = offsetY = 0;
	bScale = 1;
}
Container::Container(int h, int w)
{
	this->h = h;
	this->w = w;
	offsetX = offsetY = 0;
	bScale = 5;
	toDraw = al_create_bitmap(w, h);
	background = al_load_bitmap("transparent.png");

}

void
Container::draw(ALLEGRO_BITMAP* target)
{
	al_set_target_bitmap(toDraw);
	if(background==nullptr)
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
	al_draw_scaled_bitmap(background, offsetX, offsetY, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0,
			bScale*al_get_bitmap_width(background), bScale*al_get_bitmap_height(background), 0);
		

	for (int i=objects.size()-1;i>=0;i--)
		objects[i]->draw(toDraw);
	al_set_target_bitmap(target);
	al_draw_scaled_bitmap(toDraw, 0, 0, w, h, x, y, scale*w, scale*h, 0);
}

string
Container::click(int y, int x)
{
	for (auto& ob : objects)
	{
		if (ob->overYou(y - this->y, x - this->x) == true)
			return ob->click(y-this->y, x-this->x);
	}
	if (clickable == true && this->x <= x  &&  x <= (this->x + this->w) && this->y <= y && y <= (this->y + this->h))
	{
			clicked = true;
			return name;
	}
	return "";
}
void
Container::unClick()
{
	clicked = false;
	for (auto& x : objects)
		x->unClick();
}

bool
Container::overYou(int y, int x)
{
	for (auto& ob : objects)
		if (ob->overYou(y - this->y, x - this->x) == true)
			return true;
	if (this->x <= x  &&  x <= (this->x + this->w) && this->y <= y && y <= (this->y + this->h))
	{
		return true;
	}
	return false;
}