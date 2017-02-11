#include "Button.h"

void
Button::draw(ALLEGRO_BITMAP* target)
{
	al_set_target_bitmap(target);
	int pressed = 2, hover = 1;
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
			al_draw_tinted_scaled_bitmap(bitmaps[0],al_map_rgba(255,255,255,230)
				, 0, 0
				, al_get_bitmap_width(bitmaps[0]), al_get_bitmap_height(bitmaps[0])
				, x, y
				, scale* al_get_bitmap_width(bitmaps[0]), scale* al_get_bitmap_height(bitmaps[0])
				, 0
			);
		else
			al_draw_scaled_bitmap(bitmaps[hover]
				, 0, 0
				, al_get_bitmap_width(bitmaps[hover]), al_get_bitmap_height(bitmaps[hover])
				, x, y
				, scale* al_get_bitmap_width(bitmaps[hover]), scale* al_get_bitmap_height(bitmaps[hover])
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