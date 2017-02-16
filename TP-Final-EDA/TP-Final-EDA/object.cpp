#include "Object.h"


Object::Object()
{
	clickable = true;
	visible = true;
	dragable = false;
	hoverable = true;
	borderVisibe = false;
	clicked = false;
	hover = false;
	scale = 1;
	h = 0;
	w = 0;
	x = 0;
	y = 0;
}
Object::Object(string name, int x, int y, int h, int w, double scale)
{
	clickable = true;
	visible = true;
	dragable = false;
	hoverable = true;
	borderVisibe = false;
	clicked = false;
	hover = false;
	this->scale = scale;
	this->h = h;
	this->w = w;
	this->x = x;
	this->y = y;
	this->name = name;
}

string Object::click(int y, int x)
{
	if ( clickable == true )
	{
		//Check for x
		if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
		{
			clicked = true;
			return this->name;
		}
	}
	return "";
}

void Object::unClick(int y, int x)
{
	clicked = false;
}

bool Object::overYou(int y, int x)
{
		//Check for x
		if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
		{
			if(hoverable == true)
				hover = true;
			return true;
		}
		else
		{
			clicked = false;
			hover = false;
			return false;
		}
}
void Object::drag(int y, int x)
{
	if (dragable == true && clicked==true)
	{
		this->x = x-scale*w/2;
		this->y = y-scale*h/2;
	}
}



void Object::draw(Bitmap* target)
{
	target->setTarget();
	if(borderVisibe)
		al_draw_rectangle(x, y, x + w*scale, y + h*scale, al_map_rgb(255, 0, 0), 3);
}