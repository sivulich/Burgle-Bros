#include "HudObserver.h"

HudObserver::HudObserver(GameModel * m,BoardObserver*b, Container * c)
{
	model = m;
	boardObs = b;
	// Create the hud container
	hudCont = new Container(string("./Graphics/Images/HUD/HUD.png"));
	hudCont->setPosition(HUD_YPOS, HUD_XPOS);
	hudCont->setSize(HUD_HEIGHT, HUD_WIDTH);
	c->addObject(hudCont);

	// Create the top hud container
	topHudCont = new Container(string("./Graphics/Images/HUD/TOP HUD.png"));
	//topHudCont->setPosition();
	c->addObject(topHudCont);
	menuButton = new Image(string("./Graphics/Images/HUD/MENU.png"));
	rulesButton = new Image(string("./Graphics/Images/HUD/RULES.png"));
	topHudCont->addObject(menuButton);
	topHudCont->addObject(rulesButton);

	// Create action buttons
	// PARA PROBAR! TERMINAR DE UBICAR LOS BOTONES
	actions = { { string("MOVE"),			new Image(string("../Game/Graphics/Images/Actions/MOVE.png"),BUTTON1_XPOS,BUTTON1_YPOS,ACTION_SIZE,ACTION_SIZE)         },
				{ string("PEEK"),			new Image(string("../Game/Graphics/Images/Actions/PEEK.png"),BUTTON2_XPOS,BUTTON2_YPOS,ACTION_SIZE,ACTION_SIZE)         },
				{ string("ADD_TOKEN"),		new Image(string("../Game/Graphics/Images/Actions/ADD_TOKEN.png"),BUTTON3_XPOS,BUTTON3_YPOS,ACTION_SIZE,ACTION_SIZE)    },
				{ string("PLACE_CROW"),		new Image(string("../Game/Graphics/Images/Actions/PLACE_CROW.png"),BUTTON4_XPOS,BUTTON4_YPOS,ACTION_SIZE,ACTION_SIZE)   },
				{ string("CREATE_ALARM"),	new Image(string("../Game/Graphics/Images/Actions/CREATE_ALARM.png"),BUTTON5_XPOS,BUTTON5_YPOS,ACTION_SIZE,ACTION_SIZE) },
				{ string("SPY_PATROL"),		new Image(string("../Game/Graphics/Images/Actions/SPY_PATROL.png"),BUTTON6_XPOS,BUTTON6_YPOS,ACTION_SIZE,ACTION_SIZE)   },
				{ string("PICK_UP_LOOT"),	new Image(string("../Game/Graphics/Images/Actions/PICK_UP_LOOT.png"),BUTTON7_XPOS,BUTTON7_YPOS,ACTION_SIZE,ACTION_SIZE) },
				{ string("OFFER_LOOT"),		new Image(string("../Game/Graphics/Images/Actions/OFFER_LOOT.png"),BUTTON8_XPOS,BUTTON8_YPOS,ACTION_SIZE,ACTION_SIZE)   },
				{ string("REQUEST_LOOT"),	new Image(string("../Game/Graphics/Images/Actions/REQUEST_LOOT.png"),BUTTON9_XPOS,BUTTON9_YPOS,ACTION_SIZE,ACTION_SIZE) },
				{ string("THROW_DICE"),		new Image(string("../Game/Graphics/Images/Actions/THROW_DICE.png"),BUTTON10_XPOS,BUTTON10_YPOS,ACTION_SIZE,ACTION_SIZE) } };
	for (auto& a : actions)
	{
		a.second->disable();
		hudCont->addObject(a.second);
	}

	passButton = new Image(string("../Game/Graphics/Images/Actions/PASS.png"), (HUD_WIDTH-ACTION_SIZE)/2,HUD_HEIGHT-ACTION_SIZE, ACTION_SIZE, ACTION_SIZE);
	hudCont->addObject(passButton);
	player1 = new PlayerObserver(model->player1(), c, hudCont);
	player2 = new PlayerObserver(model->player2(), c, hudCont);

	map<characterType, string> images = { { ACROBAT,string("./Graphics/Images/Characters/The Acrobat.png") },
	{ HACKER,string("./Graphics/Images/Characters/The Hacker.png") },
	{ HAWK,string("./Graphics/Images/Characters/The Hawk.png") },
	{ JUICER,string("./Graphics/Images/Characters/The Juicer.png") },
	{ PETERMAN,string("./Graphics/Images/Characters/The Peterman.png") },
	{ RAVEN,string("./Graphics/Images/Characters/The Raven.png") },
	{ SPOTTER,string("./Graphics/Images/Characters/The Spotter.png") } };

	model->player1()->attach(this);
	model->player2()->attach(this);
	update();
}

void HudObserver::update()
{
	// If guard is moving disable all actions
	/*if (boardObs->guardIsMoving())
	{
		for (auto& a : actions)
			a.second->disable();
		passButton->disable();
	}*/
	// Else update actions
	
	{
		vector<string> possibleActions = model->currentPlayer()->getActions();
		for (auto& a : actions)
		{
			if (std::find(possibleActions.begin(), possibleActions.end(), a.first) != possibleActions.end())
				a.second->enable();
			else
				a.second->disable();
		}
		passButton->enable();
	}

}

HudObserver::~HudObserver()
{
	for (auto& a : actions)
		delete a.second;
}
