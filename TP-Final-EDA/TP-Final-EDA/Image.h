#pragma once

#include "object.h"
/*Class used to draw an image, it mantains the original aspect ratio*/
class Image :public object {
public:
	Image(string& path);
	/*Draws the image to the given bitmap*/
	void draw(ALLEGRO_BITMAP* target);
	/*Sets scale for the image to be drawn, it mantains aspect ratio*/
	void setScale(double s) { this->scale = s; };
	~Image() { if(im!=nullptr) al_destroy_bitmap(im); };
private:
	ALLEGRO_BITMAP* im;
};