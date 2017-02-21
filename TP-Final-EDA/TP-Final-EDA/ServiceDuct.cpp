#include "ServiceDuct.h"



ServiceDuct::ServiceDuct()
{
}


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