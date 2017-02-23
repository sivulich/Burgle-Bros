#pragma once
#include "../Model/Header Files/Configs.h"
#include "ALX\alx.hpp"
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

