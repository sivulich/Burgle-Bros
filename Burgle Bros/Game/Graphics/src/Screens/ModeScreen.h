#pragma once
#include <string>
#include "Image.h"
#include "Container.h"
#include "GraphicsDefs.h"
class ModeScreen :public Container
{
public:
	ModeScreen(Container* p);
private:
	Container* parent;
};