#pragma once

#include "../../View/Header Files/Screen.h"
#include "../../Model/Header Files/Configs.h"
#include "controller.h"
#include "../../View/Header Files/ALX/alx.hpp"

class localControler {
public:
	localControler(Screen* source);
	string input();
	~localControler();
private:
	Screen* source;
	ALLEGRO_EVENT_QUEUE* events;
	ALLEGRO_EVENT event;
	bool mPressed;
};*/