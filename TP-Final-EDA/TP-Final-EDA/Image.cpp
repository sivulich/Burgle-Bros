
#include "Image.h"


Image::Image(string& path)
{
	im.load(path.c_str());
	h = im.getHeight();
	w = im.getWidth();
	size_t pos = path.find('.');
	name = path.substr(0, pos);

}
void
Image::draw(Bitmap* target)
{
	target->setTarget();
	if(hover==true)
		im.drawTintedScaled(HOVER_TONE, 0, 0, w, h, x, y, scale*w, scale*h, 0);
	else
		im.drawScaled( 0, 0, w, h, x, y, scale* w, scale*h, 0);
}