#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\bitmap.h>
#include "Configs.h"
class object {
public:
	object();
	virtual void draw();
	void setPosition(int x, int y) { this->x = x; this->y = y; };
	void setVisible(bool b) { visible = b; };
	void setDragable(bool b) { dragable = b; };
	void setClickable(bool b) { clickable = b; };
	void setName(string& s) { name = s; };
	virtual string click(int x, int y) { return ""; };
	pair<int, int> getPos() { pair<int, int> pos(x, y); return pos; };
protected:
	/*Properties*/
	bool dragable, clickable;
	/*States*/
	bool visible,clicked, hover;
	int x, y;
	string name;
};

/*Class used to pack many objects to a closed form, all objects will be drawn with its position relative to parents position
* and with the parents scale (pScale*cScale*size)*/
class container:public object {
public:
	/*Draws the container with all the child objects inside*/
	void draw(ALLEGRO_BITMAP* target);
	/*Sets the background for the given container*/
	void setBackground(ALLEGRO_BITMAP* b);
	//Changes the properties of the background
	void backgroundProperties(int offsetX, int offsetY, double bScale);

	/*Adds an object to the parent container*/
	void addObject(object* ob) { objects.push_back(ob); };

	/*Sets the size in pixels, within the parent container*/
	void setSize(int h, int w) { this->h = h; this->w = w; };
	/*Sets the scale to draw the container (height*scale and width*scale)*/
	void setScale(double s) { scale = s; };

	/*Checks if mouse is over the container*/
	bool overYou(int x, int y);
	//returns the name of what you pressed, can be container or object within the container
	string click(int x, int y);
private:
	/*Background info*/
	ALLEGRO_BITMAP* background;
	int offsetX, offsetY; //Used to offset the drawing of the background in the given container
	double bScale; //Used to scale up or down the given backGround

	/*Container info*/
	int h, w;
	double scale;

	/*Child objects for the given container*/
	vector<object*> objects;
};

/*Class used to draw an image, it mantains the original aspect ratio*/
class image :public object {
public:
	/*Draws the image to the given bitmap*/
	void draw(ALLEGRO_BITMAP* target);
	/*Set image to draw*/
	void setImage(ALLEGRO_BITMAP* im) { this->im = im; };
	/*Sets scale for the image to be drawn, it mantains aspect ratio*/
	void setScale(double s) { this->scale = s; };
	/*Returns true if mouse is over the image*/
	bool overYou(int x, int y);
	/*Returns image name if clicked*/
	string click(int x, int y);
private:
	double scale;
	ALLEGRO_BITMAP* im;
};