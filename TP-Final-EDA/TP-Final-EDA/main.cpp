
#include "Screen.h"
#include "Image.h"
#include "Container.h"
#include "Button.h"


int main(void)
{
	string background = "background.jpg";
	string name = "Button";
	Screen mainScreen(720, 1280, background);
	Button testButton(name);
	Image testImage;
	
	vector<string> paths = { "button.png","button_pressed.png" };
	testButton.setImages(paths);
	testImage.setImage(background);
	testImage.setScale(0.1);
	testImage.setPosition(400, 400);
	testButton.setPosition(100, 100);
	mainScreen.addObject(&testButton);
	mainScreen.addObject(&testImage);
	mainScreen.backgroundProperties(0, 0, 0.66666);
	al_install_mouse();
	while (1)
	{
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		mainScreen.overYou(state.y, state.x);
		if (state.buttons & 1)
			mainScreen.click(state.y, state.x);
		else
			mainScreen.unClick();
		mainScreen.draw();
	}
		
	
}