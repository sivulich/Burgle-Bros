#pragma once

#include <object.h>
#include <Font.hpp>

// Text object
class Text : public Object
{
public:
	Text(string font);
	Text(string font, Color c, int size, int xpos, int ypos);
	Text(string font,string content, Color c, int size, int xpos, int ypos);
	void setText(string s);
	string getText() { return content; };
	virtual void draw(Bitmap* target)override;

private:
	string content;
	Font * f;
	Color color;
};