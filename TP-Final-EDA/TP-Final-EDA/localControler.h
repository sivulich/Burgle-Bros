#pragma once
#include "Screen.h"
#include "Configs.h"
#include "controller.h"
class localControler :public controller {
public:
	localControler(Screen* source);
	string input();
	~localControler();
private:
	Screen* source;
	ALLEGRO_EVENT_QUEUE* events;
	ALLEGRO_EVENT event;

};