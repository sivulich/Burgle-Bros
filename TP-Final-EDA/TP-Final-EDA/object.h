#pragma once

#include "Configs.h"
class Object {
public:
	Object();
	Object(string name, int x, int y, int h, int w, double scale);
	virtual void draw(Bitmap* target);
	/*Sets the scale to draw the object (height*scale and width*scale)*/
	void setScale(double s) { scale = s; };
	/*Set position for the given object*/
	void setPosition(int y, int x) { this->x = x; this->y = y; };
	/*Set the size for the given object*/
	virtual void setSize(int h, int w) { this->h = h; this->w = w; };
	/*Default true*/
	void setVisible(bool b) { visible = b; };
	/*Default false*/
	void setDragable(bool b) { dragable = b; };
	/*Default true*/
	void setClickable(bool b) { clickable = b; };
	/*Sets the name for the object*/
	void setName(string& s) { name = s; };
	/*Returns the position of the object*/
	pair<int, int> getPos() { pair<int, int> pos(x, y); return pos; };
	/*Returns the size of the object*/
	pair<int, int> getSize() { pair<int, int> size(h, w); return size; };
	/*Checks if mouse is over the object*/
	virtual bool overYou(int y, int x);
	/*By default returns the name of the object clicked*/
	virtual string click(int y, int x);
	virtual void unClick(int y, int x);
	/*Drag*/
	virtual void drag(int y, int x);
protected:
	/*Properties*/
	bool dragable,clickable,hoverable; // Hoverable?! jajaj :')
	/*States*/
	bool visible,clicked, hover;

	/*Properties of the object*/
	//Y corresponds to the vertical position within the screen
	//X to the horizontal position
	int y, x;
	int h, w;
	double scale;
	string name;
};





