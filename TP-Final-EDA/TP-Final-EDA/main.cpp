
#include "Screen.h"
#include "Image.h"
#include "Container.h"
#include "Button.h"
#include "localControler.h"
#include "Textbox.h"
int main(void)
{
	string background = "background.jpg";
	string hud = "hudTest.png";
	string name = "testChar";
	string peek = "peek";
	string move = "move";
	string font = "Raleway-Black.ttf";
	Screen mainScreen(720, 1280, background);
	Container testCont(hud);
	Image testImage(name + ".jpg");
	Image peekImage(peek + ".png");
	Image moveImage(move + ".png");
	
	Textbox tbox(10, 10, font, 10, 50);
	Timer draw(1.0 / 60.0);
	moveImage.setScale(0.7);
	moveImage.setPosition(185, 420);
	testCont.addObject(&moveImage);
	peekImage.setScale(0.3);
	peekImage.setPosition(170, 600);
	testCont.addObject(&peekImage);
	testCont.addObject(&testImage);
	testImage.setPosition(100, 30);
	testImage.setScale(0.51);
	testCont.setScale(0.666);
	testCont.setPosition(473,0);
	mainScreen.addObject(&testCont);
	mainScreen.backgroundProperties(0, 0, 0.66666);
	mainScreen.addObject(&tbox);
	testImage.setDragable(true);
	testCont.setDragable(true);

	localControler control(&mainScreen);
	string in;
	Image* test = nullptr;
	int count = 0;
	draw.start();
	while ((in=control.input())!="exit")
	{
		if (in != "")
			cout << "Input was " << in << endl;
		if (in == (name + "zoom"))
		{
			mainScreen.removeObject(test);
			delete test;
			test = nullptr;
		}
		if (in == name && test==nullptr)
		{

			test = new Image(name + ".jpg");
			test->setPosition(50, 350);
			test->setName(name+"zoom");
			mainScreen.addObject(test);
		}
		if (count < draw.getCount())
		{
			mainScreen.draw();
			count = draw.getCount();
		}
	}
		
	return 0;
}