#include "./object.h"

// Default constructor
Object::Object()
{
	clickable = true;
	visible = true;
	dragable = false;
	hoverable = true;
	disabled = false;
	borderVisibe = false;
	clicked = false;
	hover = false;
	initOk = false;
	scaleY = 1;
	scaleX = 1;
	alpha = 1.0;
	h = 0;
	w = 0;
	x = 0;
	y = 0;
}

// Constructor that sets the name, the x pos, the y pos, height, width and scale
Object::Object(string name, int x, int y, int h, int w, double scale)
{
	clickable = true;
	visible = true;
	dragable = false;
	hoverable = true;
	disabled = false;
	borderVisibe = false;
	clicked = false;
	hover = false;
	initOk = false;
	scaleX = scale;
	scaleY = scale;
	alpha = 1.0;
	this->h = h;
	this->w = w;
	this->x = x;
	this->y = y;
	this->name = name;	
}

string Object::click(int y, int x)
{
	if (initOk == true)
	{
		if (clickable)
		{
			if (isInside(y, x))
			{
				DEBUG_MSG("Clicking object " << name);
				clicked = true;
				return this->name;
			}
			else return "";
		}
		else return "Not Clickable";
		//DEBUG_MSG_V("Trying to click object " << name << " when is not clickable");
	}
	else DEBUG_MSG("Trying to click object " << name << " when is not initialized correctly");

	return "";
}

void Object::unClick(int y, int x)
{
		clicked = false;
}

bool Object::overYou(int y, int x)
{
	if (initOk == true)
	{
		if (isInside(y, x))
		{
			if (hoverable)
			{
				hover = true;
				DEBUG_MSG_V("Hovering " << name);
				return true;
			}
		}
		else 
		{
			clicked = false;
			hover = false;
			return false;
		}
	}
	else
		DEBUG_MSG("Trying to hover object " << name << " when is not initialized correctly");
	return false;
}

void Object::drag(int y, int x)
{
	if (initOk == true && dragable == true && clicked == true)
	{
		DEBUG_MSG_V("Draging " << name);
		this->x = x - scaleX*w / 2;
		this->y = y - scaleY*h / 2;
	}
	else
		DEBUG_MSG("Trying to drag object " << name << " when is not initialized correclty");
}



void Object::draw(Bitmap* target)
{
	if (initOk == true && target != nullptr && target->get() != nullptr)
	{
		target->setTarget();
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
		al_draw_rectangle(x, y, x + w*scaleX, y + h*scaleY, al_map_rgb(255, 0, 0), 3);
}


bool Object::isInside(int y, int x)
{
	return this->x <= x  &&  x <= (this->x + scaleX*this->w) && this->y <= y && y <= (this->y + scaleY*this->h);
}

void Object::playAnimation()
{
	if (hasAnimation())
	{
		animation.front()->play(this);
		if (animation.front()->hasEnded())
		{
			delete animation.front();
			animation.pop();
		}
	}
}


