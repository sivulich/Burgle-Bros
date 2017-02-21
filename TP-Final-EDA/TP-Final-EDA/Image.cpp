
#include "Image.h"


Image::Image(string& path)
{
	im.load(path.c_str());
	h = im.getHeight();
	w = im.getWidth();
	size_t pos = path.find('.');
	size_t pos2 = path.find_last_of('/');
	size_t pos3 = path.find_last_of('\\');
	if (pos2 == string::npos)
		pos2 = 0;
	if (pos3 != string::npos)
		pos2 = pos3;
	name = path.substr(pos2+1, pos);

}
void
Image::draw(Bitmap* target)
{
	target->setTarget();
	if(hover==true)
		im.drawTintedScaled(HOVER_TONE, 0, 0, w, h, x, y, scale*w, scale*h, 0);
	else
		im.drawScaled( 0, 0, w, h, x, y, scale* w, scale*h, 0);

	if(borderVisibe)
		al_draw_rectangle(x, y, x + w*scale, y + h*scale, al_map_rgb(255, 0, 0), 3);
}