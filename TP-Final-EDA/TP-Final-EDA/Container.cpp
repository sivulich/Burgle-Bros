
#include "Container.h"

Container::Container(string& path)
{
	background.load(path.c_str());
	
	h = background.getHeight();
	w = background.getWidth();
	toDraw = new Bitmap(w, h);
	offsetX = offsetY = 0;
	bScale = 1;
}
Container::Container(int h, int w)
{
	this->h = h;
	this->w = w;
	offsetX = offsetY = 0;
	bScale = 5;
	toDraw = new Bitmap(w, h);
	background.load("transparent.png");

}

void
Container::draw(Bitmap* target)
{
	toDraw->setTarget();
	al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
	if(background._Get()==nullptr)
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
	else
		background.drawScaled( offsetX, offsetY, background.getWidth(), background.getHeight(), 0, 0,
			bScale*background.getWidth(), bScale*background.getHeight(), 0);
		

	for (int i=objects.size()-1;i>=0;i--)
		objects[i]->draw(toDraw);
	target->setTarget();
	toDraw->drawScaled( 0, 0, w, h, x, y, scale*w, scale*h, 0);
}

string
Container::click(int y, int x)
{
	for (auto& ob : objects)
	{
		if (ob->overYou((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale)) == true)
			return ob->click((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale));
	}
	if (clickable == true && this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
			clicked = true;
			return name;
	}
	return "";
}
void
Container::unClick(int y, int x)
{
	clicked = false;
	for (auto& ob : objects)
		ob->unClick((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale));
}

bool
Container::overYou(int y, int x)
{
	for (auto& ob:objects)
		if (ob->overYou((y - this->y)*(1.0/scale), (x - this->x)*(1.0/scale)) == true)
			return true;

	if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		return true;
	}
	return false;
}

void
Container::drag(int y, int x)
{
	for (auto& ob : objects)
		if (ob->overYou((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale)) == true)
		{
			ob->drag((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale));
			return;
		}
	if (dragable==true &&this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		this->x = x - scale*w / 2;
		this->y = y - scale*h / 2;
	}
}