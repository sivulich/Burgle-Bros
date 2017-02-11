#pragma once

#include "object.h"
/*Class used to pack many objects to a closed form, all objects will be drawn with its position relative to parents position
* and with the parents scale (pScale*cScale*size)*/
class Container :public object {
public:
	/*This constructor should be used when setting a background to fill the container*/
	Container(string& path);
	//This constructor sets a fixed size to where the background will be drawn with the given offsets
	Container(int height, int width);
	/*Draws the container with all the child objects inside*/
	void draw(ALLEGRO_BITMAP* target);
	/*Sets the background for the given container*/
	void setBackground(string& path) { background = al_load_bitmap(path.c_str()); };
	//Changes the properties of the background
	void backgroundProperties(int offsetX, int offsetY, double bScale) { this->offsetX = offsetX; this->offsetY = offsetY; this->bScale = bScale; };

	/*Adds an object to the parent container*/
	void addObject(object* ob) { objects.insert(objects.begin(),ob); };

	/*Sets the size in pixels, within the parent container*/
	void setSize(int h, int w) { this->h = h; this->w = w; };
	/*returns the name of what you pressed, can be container or object within the container*/
	string click(int y, int x);
	bool overYou(int y, int x);
	void unClick();
private:

	/*Background info*/
	ALLEGRO_BITMAP* background;
	int offsetX, offsetY; //Used to offset the drawing of the background in the given container
	double bScale; //Used to scale up or down the given backGround

	/*Container utility*/
	ALLEGRO_BITMAP* toDraw;

	/*Child objects for the given container*/
	vector<object*> objects;
};