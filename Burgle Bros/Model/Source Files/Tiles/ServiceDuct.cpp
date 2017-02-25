#include "../../Header Files/Tiles/ServiceDuct.h"





ServiceDuct::~ServiceDuct()
{
}

void ServiceDuct::setOtherSide(ServiceDuct* t)
{
	otherSide = t;
}


bool ServiceDuct::isOpen()
{
	return otherSide->isFlipped();
}