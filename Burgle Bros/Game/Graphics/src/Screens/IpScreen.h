#pragma once
#include <string>
#include "Image.h"
#include "Textbox.h"
#include "Container.h"
#include "GraphicsDefs.h"
class IpScreen:public Container
{
public:
	IpScreen(Container* p);
	string getIp();
	~IpScreen();
private:
	Container* parent;
	Textbox* textBox;
};

