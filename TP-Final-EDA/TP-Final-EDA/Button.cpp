#include "Button.h"

void
Button::draw(ALLEGRO_BITMAP* target)
{
	al_set_target_bitmap(target);
	int pressed = 2;
	if (bitmaps.size() == 2)
	{
		pressed = 1;

	}
	if (clicked == true)
		al_draw_scaled_bitmap(bitmaps[pressed]
			, 0, 0
			, al_get_bitmap_width(bitmaps[pressed]), al_get_bitmap_height(bitmaps[pressed])
			, x, y
			, scale* al_get_bitmap_width(bitmaps[pressed]), scale* al_get_bitmap_height(bitmaps[pressed])
			, 0
		);
	else if (hover == true)
		if(pressed==1)
			al_draw_tinted_scaled_bitmap(bitmaps[0],HOVER_TONE
				, 0, 0
				, al_get_bitmap_width(bitmaps[0]), al_get_bitmap_height(bitmaps[0])
				, x, y
				, scale* al_get_bitmap_width(bitmaps[0]), scale* al_get_bitmap_height(bitmaps[0])
				, 0
			);
		else
			al_draw_scaled_bitmap(bitmaps[1]
				, 0, 0
				, al_get_bitmap_width(bitmaps[1]), al_get_bitmap_height(bitmaps[1])
				, x, y
				, scale* al_get_bitmap_width(bitmaps[1]), scale* al_get_bitmap_height(bitmaps[1])
				, 0
			);
	else
		al_draw_scaled_bitmap(bitmaps[0]
			, 0, 0
			, al_get_bitmap_width(bitmaps[0]), al_get_bitmap_height(bitmaps[0])
			, x, y
			, scale* al_get_bitmap_width(bitmaps[0]), scale* al_get_bitmap_height(bitmaps[0])
			, 0
		);

}

void
Button::setImages(vector<string>& files)
{
	for (auto& x : files)
		bitmaps.push_back(al_load_bitmap(x.c_str()));
	h = al_get_bitmap_height(bitmaps[0]);
	w = al_get_bitmap_width(bitmaps[0]);
}