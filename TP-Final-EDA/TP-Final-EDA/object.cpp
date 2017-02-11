#include "object.h"

object::object()
{
	clickable = true;
	visible = true;
	dragable = false;
	clicked = false;
	hover = false;
	scale = 1;
	h = 0;
	w = 0;
	x = 0;
	y = 0;
}

string
object::click(int y, int x)
{
	if ( clickable == true )
	{
		//Check for x
		if (this->x <= x  &&  x <= (this->x + this->w))
		{
			//check for y
			if (this->y <= y && y <= (this->y + this->h))
			{
				clicked = true;
				return this->name;
			}
		}
	}
	return "";
}

void
object::unClick()
{
	clicked = false;
}

bool
object::overYou(int y, int x)
{
		//Check for x
		if (this->x <= x  &&  x <= (this->x + this->w) && this->y <= y && y <= (this->y + this->h))
		{
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
void
object::drag(int y, int x)
{
	if (dragable == true)
	{
		this->x = x;
		this->y = y;
	}
}