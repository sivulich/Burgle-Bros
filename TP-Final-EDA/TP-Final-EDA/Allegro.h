#pragma once
#include "Configs.h"
class Allegro
{
public:
	/*Initializes and deinitializes the allegro library*/
	Allegro();
	~Allegro();
	bool wasInitOk() { return initOk; };
private:
	bool initOk = false;
};

