#pragma once
#include "../../View/Header Files/Observers/Observer.h"
#include <list>

class BaseModel
{
public:
	void attach(Observer* o) { observers.push_back(o); }
	void detach(Observer* o) { observers.remove(o); } 

protected:
	void update()
	{
		for(auto& obs : observers)
			obs->update();
	}

private:
	std::list<Observer*> observers;
};

