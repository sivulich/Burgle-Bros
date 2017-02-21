#pragma once
#include "Configs.h"
class Allegro
{
public:
	Allegro();
	~Allegro();
	bool wasInitOk() { return initOk; };
private:
	bool initOk = false;
};

