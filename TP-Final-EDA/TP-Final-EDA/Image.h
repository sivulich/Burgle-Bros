#pragma once

#include "object.h"
/*Class used to draw an image, it mantains the original aspect ratio*/
class Image :public object {
public:
	Image(string& path) { this->im = al_load_bitmap(path.c_str()); h = al_get_bitmap_height(im); w = al_get_bitmap_width(im); };
	/*Draws the image to the given bitmap*/
	void draw(ALLEGRO_BITMAP* target);
	/*Sets scale for the image to be drawn, it mantains aspect ratio*/
	void setScale(double s) { this->scale = s; };
	~Image() { if(im!=nullptr) al_destroy_bitmap(im); };
private:
	ALLEGRO_BITMAP* im;
};