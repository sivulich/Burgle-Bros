#include "../../Header Files/Observers/ActionObserver.h"


ActionObserver::ActionObserver(Player* p, int separation, int max, Container* pa)
{
	player = p;
	this->max = max;
	this->separation = separation;
	parent = pa;
	actionBox = new Container(200, separation*(max-1)+200 * max);
	actionBox->setScale(pa->getWidth()*1.0 / 3.0/actionBox->getWidth());
	actions = {	{string("MOVE"),Image(string("../View/Images/Actions/MOVE.png"))},
				{string("PEEK"),Image(string("../View/Images/Actions/PEEK.png"))},
				{string("ADD_TOKEN"),Image(string("../View/Images/Actions/ADD_TOKEN.png"))},
				{string("PLACE_CROW"),Image(string("../View/Images/Actions/PLACE_CROW.png"))},
				{ string("CREATE_ALARM"),Image(string("../View/Images/Actions/CREATE_ALARM.png")) }
	};
	for (auto& act : actions)
	{
		act.second.setScale(200.0 / act.second.getHeight());
		act.second.setBorderVisible(true);
	}
	actionBox->setPosition(0.9*parent->getHeight()-actionBox->getScale()*actionBox->getHeight(), double(pa->getWidth()) / 3.0);
	pa->addObject(actionBox);
}
void
ActionObserver::update()
{
	int x=0,added=0;
	actionBox->clear();
	for (auto& action : player->getActions())
	{
		if (added < max)
		{
			if (action == "MOVE" || action == "PEEK" || action == "ADD_TOKEN" || action == "PLACE_CROW" || action == "CREATE_ALARM")
			{
				actionBox->addObject(&actions[action]);
				actions[action].setPosition(0, x);
				added++;
				x += (actionBox->getWidth() - separation*(max - 1)) / max + separation;
			}
		}
	}
}



ActionObserver::~ActionObserver()
{
	if (actionBox != nullptr)
		delete actionBox;
}