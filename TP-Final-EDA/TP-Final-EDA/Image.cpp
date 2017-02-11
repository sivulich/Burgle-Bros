
#include "Image.h"


void
Image::draw(ALLEGRO_BITMAP* target)
{
	al_set_target_bitmap(target);
	if(hover==true)
		al_draw_tinted_scaled_bitmap(im,HOVER_TONE, 0, 0, al_get_bitmap_width(im), al_get_bitmap_height(im), x, y, scale* al_get_bitmap_width(im), scale*al_get_bitmap_height(im), 0);
	else
		al_draw_scaled_bitmap(im, 0, 0, al_get_bitmap_width(im), al_get_bitmap_height(im), x, y, scale* al_get_bitmap_width(im), scale*al_get_bitmap_height(im), 0);
}