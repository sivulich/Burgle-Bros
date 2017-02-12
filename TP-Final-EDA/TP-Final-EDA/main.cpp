
#include "Screen.h"
#include "Image.h"
#include "Container.h"
#include "Button.h"
#include "localControler.h"

int main(void)
{
	string background = "background.jpg";
	string hud = "hudTest.png";
	string name = "testChar";
	Screen mainScreen(720, 1280, background);
	Container testCont(hud);
	Image testImage(name + ".jpg");
	testImage.setName(name);
	testCont.addObject(&testImage);
	testImage.setPosition(100, 30);
	testImage.setScale(0.51);
	testCont.setScale(0.666);
	testCont.setPosition(473,0);
	mainScreen.addObject(&testCont);
	mainScreen.backgroundProperties(0, 0, 0.66666);



	localControler control(&mainScreen);
	string in;
	Image* test = nullptr;
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
		if (in == name)
		{

			test = new Image(name + ".jpg");
			test->setPosition(50, 350);
			test->setName(name+"zoom");
			mainScreen.addObject(test);
		}
		mainScreen.draw();
	}
		
	return 0;
}