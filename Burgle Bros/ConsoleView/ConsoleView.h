#pragma once
#include "Observer.h"
#include "../Model/Header Files/GameModel.h"

class ConsoleView :	public Observer
{
public:
	ConsoleView(GameModel* m)
	{
		model = m;
		model->attach(this);
	}

	~ConsoleView() {};

	virtual void update()
	{
		
	}

	void draw()
	{
		model->print();
	}

private:
	GameModel * model;

};

