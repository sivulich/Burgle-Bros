#pragma once

#include "Configs.h"
class Object {
public:
	/**
		Default constructor
	*/
	Object();

	/**
		
	*/
	Object(string name, int x, int y, int h, int w, double scale);

	/**
	
	*/
	virtual void draw(Bitmap* target);

	/** 
		Sets the scale to draw the object 
	*/
	void setScale(double s) { scale = s; };

	/** 
		Set position for the object
	*/
	void setPosition(int y, int x) { this->x = x; this->y = y; };

	/**  
		Set the size for the given object
	*/
	virtual void setSize(int h, int w) { this->h = h; this->w = w; };

	/** 
		Set the visibility of the object in screen
	*/
	void setVisible(bool b) { visible = b; };
	
	/** 
		
	*/
	void setDragable(bool b) { dragable = b; };
	
	/** 
		
	*/
	void setClickable(bool b) { clickable = b; };
	
	/**
	
	*/
	void setBorderVisible(bool b) { borderVisibe = b; };
	/** 
		Sets the name for the object	
	*/
	void setName(string& s) { name = s; };

	/** 
		Returns the position of the object
	*/
	pair<int, int> getPos() { pair<int, int> pos(x, y); return pos; };
	
	/**
	
	*/
	int getWidth() { return w; };


	/**
	
	*/
	int getHeight() { return h; };

	/** 
		Returns the size of the object
	*/
	pair<int, int> getSize() { return pair<int, int>(h, w); };
	
	/** 
		Checks if point is over the object
	*/
	virtual bool overYou(int y, int x);
	
	/** 

	*/
	virtual string click(int y, int x);

	/**
	
	*/
	virtual void unClick(int y, int x);
	
	/** 
		Drag
	*/

	virtual void drag(int y, int x);

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
};





