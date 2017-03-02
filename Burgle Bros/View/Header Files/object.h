#pragma once

#include "../../Model/Header Files/Configs.h"
#include "../Header Files/ALX/alx.hpp"
using namespace alx;
class Object
{
public:
	/** Default constructor*/
	Object();

	/** Constructor that sets the name, the x pos, the y pos, height, width and scale
		@param name Name for the object
		@param x X position
		@param y Y position
		@param h Height
		@param w Width
		@param scale Scale
	*/
	Object(string name, int x, int y, int h, int w, double scale);

	/** Returns a nullptr it can be overloaded for diferent pruposes*/
	virtual Bitmap* getTarget() { return nullptr; };

	/** Draws the object to the given target
		@param target Target to draw the object on
	*/
	virtual void draw(Bitmap* target);

	/** Sets the scale to draw the object 
		@param s Scale
	*/
	void setScale(double s) { scale = s; };

	/** Set position for the object
		@param y Y position
		@param x X position
	*/
	void setPosition(int y, int x) { this->x = x; this->y = y; };

	/**  Set the size for the given object
		@param h Height
		@param w Width
	*/
	virtual void setSize(int h, int w) { this->h = h; this->w = w; };

	/** Set the visibility of the object in screen*/
	void setVisible(bool b) { visible = b; };
	
	/** Set whether the object is dragable or not*/
	void setDragable(bool b) { dragable = b; };
	
	/** Set whether the object is clickable or not*/
	void setClickable(bool b) { clickable = b; };
	
	/** Sets if the border is visible in the object*/
	void setBorderVisible(bool b) { borderVisibe = b; };
	/** 
		Sets the name for the object	
	*/
	void setName(string& s) { name = s; };

	/** Returns the position of the object*/
	pair<int, int> getPos() { return pair<int, int>(y,x); };
	
	/** Returns the width of the object*/
	int getWidth() { return w; };

	/** Returns the height of the object*/
	int getHeight() { return h; };

	/** Returns the size of the object*/
	pair<int, int> getSize() { return pair<int, int>(h, w); };
	
	/** Checks if point is over the object
		@param y Mouse Y position
		@param x Mouse X position
	*/
	virtual bool overYou(int y, int x);
	
	/** Returns the object name if clicked
		@param y Mouse Y position
		@param x Mouse X position
	*/
	virtual string click(int y, int x);

	/** Unclicks the object
		@param y Mouse Y position
		@param x Mouse X position
	*/
	virtual void unClick(int y, int x);
	
	/** Drag the object
		@param y Mouse Y position
		@param x Mouse X position
	*/
	virtual void drag(int y, int x);

	/** 
	
	*/
	virtual bool isClicked() { return clicked; };

	bool wasInitOk() { return initOk; };

	double getScale() { return scale; };
protected:
	/** 
		Properties
	*/
	bool dragable,clickable,hoverable,borderVisibe; 
	
	/** 
		States
	*/
	bool visible,clicked,hover;

	/** 
	Properties of the object
	*/	
	int y, x;  //Y vertical, X horizontal position
	int h, w;
	double scale;
	string name;
	bool initOk;
};





