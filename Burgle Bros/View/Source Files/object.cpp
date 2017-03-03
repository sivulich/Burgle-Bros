#include "../Header Files/object.h"


Object::Object()
{
	clickable = true;
	visible = true;
	dragable = false;
	hoverable = true;
	borderVisibe = false;
	clicked = false;
	hover = false;
	initOk = false;
	animation = nullptr;
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
	animation = nullptr;
}

string Object::click(int y, int x)
{
	if (initOk == true && clickable == true)
	{
		//Check for x
		if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
		{
			DEBUG_MSG_V("Clicking object " << name);
			clicked = true;
			return this->name;
		}
	}
	else if (initOk == true)
		DEBUG_MSG_V("Trying to click object " << name << " when is not clickable");
	else
		DEBUG_MSG("Trying to click object " << name << " when is not initialized correctly");
	return "";
}

void Object::unClick(int y, int x)
{
	if (initOk == true)
	{
		clicked = false;
		DEBUG_MSG_V("Unclicking " << name);
	}
	else
		DEBUG_MSG("Trying to unclick object " << name << " when is not initialized correctly");
}

bool Object::overYou(int y, int x)
{
		//Check for x
	if (initOk == true && this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		if (hoverable == true)
		{
			hover = true;
		}
		DEBUG_MSG_V("Hovering " << name);
		return true;
	}
	else if (initOk == true)
	{
		clicked = false;
		hover = false;
		return false;
	}
	else
		DEBUG_MSG("Trying to hover object " << name << " when is not initialized correctly");
}
void Object::drag(int y, int x)
{
	if (initOk == true && dragable == true && clicked == true)
	{
		DEBUG_MSG_V("Draging " << name);
		this->x = x - scale*w / 2;
		this->y = y - scale*h / 2;
	}
	else
		DEBUG_MSG("Trying to drag object " << name << " when is not initialized correclty");
}



void Object::draw(Bitmap* target)
{
	if (initOk == true && target != nullptr && target->get() != nullptr)
	{
		target->setTarget();
		if (hasAnimation())
		{
			animation->play(this);
			if (animation->hasEnded())
				delete animation;
		}		
	}
	else
	{
		if (initOk == true)
			DEBUG_MSG("Error while trying to draw object " << name << " target was not initialized correctly");
		else
			DEBUG_MSG("Error while trying to draw object" << name << ", object was not initialized correctly");
		return;
	}
	DEBUG_MSG_V("Drawing " << name);
	if(borderVisibe)
		al_draw_rectangle(x, y, x + w*scale, y + h*scale, al_map_rgb(255, 0, 0), 3);
}