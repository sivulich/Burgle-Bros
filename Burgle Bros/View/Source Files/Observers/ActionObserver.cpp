#include "../../Header Files/Observers/ActionObserver.h"


ActionObserver::ActionObserver(Player* p, int separation, int max, Container* pa)
{
	int H = 300;
	player = p;
	this->max = max;
	this->separation = separation;
	parent = pa;
	actionBox = new Container(H, separation*(max-1)+H * max);
	actionBox->setScale(parent->getHeight()*0.40 / actionBox->getHeight());
	actions = {	{string("MOVE"),Image(string("../View/Images/Actions/MOVE.png"))},
				{string("PEEK"),Image(string("../View/Images/Actions/PEEK.png"))},
				{string("ADD_TOKEN"),Image(string("../View/Images/Actions/ADD_TOKEN.png"))},
				{string("PLACE_CROW"),Image(string("../View/Images/Actions/PLACE_CROW.png"))},
				{ string("CREATE_ALARM"),Image(string("../View/Images/Actions/CREATE_ALARM.png")) },
				{string("SPY_PATROL"),Image(string("../View/Images/Actions/SPY_PATROL.png"))},
				{ string("PICK_UP_LOOT"),Image(string("../View/Images/Actions/PICK_UP_LOOT.png")) }
	};
	buttons = { {string("OFFER_LOOT"),Button(string("OFFER_LOOT"),vector<string>(1,string("../View/Images/Buttons/OFFER_LOOT.png")))},
				{ string("PASS"),Button(string("PASS"),vector<string>(1,string("../View/Images/Buttons/PASS.png"))) },
				{ string("REQUEST_LOOT"),Button(string("REQUEST_LOOT"),vector<string>(1,string("../View/Images/Buttons/REQUEST_LOOT.png"))) },
				{ string("THROW_DICE"),Button(string("THROW_DICE"),vector<string>(1,string("../View/Images/Buttons/THROW_DICE.png"))) }
	};
	int X=1600, Y=150;
	buttons[string("OFFER_LOOT")].setPosition(Y, X);
	parent->addObject(&buttons[string("OFFER_LOOT")]);
	buttons[string("PASS")].setPosition(Y+50, X);
	parent->addObject(&buttons[string("PASS")]);
	buttons[string("REQUEST_LOOT")].setPosition(Y+100, X);
	parent->addObject(&buttons[string("REQUEST_LOOT")]);
	buttons[string("THROW_DICE")].setPosition( Y+150, X);
	parent->addObject(&buttons[string("THROW_DICE")]);
	for (auto& act : actions)
	{
		act.second.setScale(double(actionBox->getHeight())/ act.second.getHeight());
		act.second.setBorderVisible(false);
	}
	actionBox->setPosition(0.5*parent->getHeight(), double(pa->getWidth()) / 4.0);
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
			if(actions.find(action)!=actions.end())
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