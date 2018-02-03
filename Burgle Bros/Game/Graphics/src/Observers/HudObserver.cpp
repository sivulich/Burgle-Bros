#include "HudObserver.h"

HudObserver::HudObserver(GameModel * m,BoardObserver*b, Container * c)
{
	model = m;
	boardObs = b;
	// Create the hud container
	hudCont = new Container(string("./Graphics/Images/HUD/HUD.png"));
	hudCont->setPosition(592,118);
	hudCont->setSize(115,1044);
	c->addObject(hudCont);

	// Create the top hud container
	topHudCont = new Container(string("./Graphics/Images/HUD/TOP HUD.png"));
	topHudCont->setPosition(5,196);
	c->addObject(topHudCont);

	pauseButton = new Image(string("./Graphics/Images/HUD/PAUSE.png"),8,17);
	exitButton = new Image(string("./Graphics/Images/HUD/EXIT.png"),803,17);
	yesButton = new Image(string("../Game/Graphics/Images/Actions/YES.png"), 8, 17);// ESTO ES DE PRUEBA PROQ NO SE USAR QUESTION BOX
	noButton = new Image(string("../Game/Graphics/Images/Actions/NO.png"), 803, 17);// ESTO ES DE PRUEBA PROQ NO SE USAR QUESTION BOX
	topHudCont->addObject(yesButton);// ESTO ES DE PRUEBA PROQ NO SE USAR QUESTION BOX
	topHudCont->addObject(noButton);// ESTO ES DE PRUEBA PROQ NO SE USAR QUESTION BOX
	topHudCont->addObject(pauseButton);
	topHudCont->addObject(exitButton);

	// Create action buttons

	actions = { { string("MOVE"),			new Image(string("../Game/Graphics/Images/Actions/MOVE.png"),295,23) },
				{ string("PEEK"),			new Image(string("../Game/Graphics/Images/Actions/PEEK.png"),365,23) },
				{ string("ADD_TOKEN"),		new Image(string("../Game/Graphics/Images/Actions/ADD_TOKEN.png"),505,23) },
				{ string("USE_TOKEN"),		new Image(string("../Game/Graphics/Images/Actions/USE_TOKEN.png"),534,23) },
				{ string("PICK_UP_LOOT"),	new Image(string("../Game/Graphics/Images/Actions/PICK_UP_LOOT.png"),663,23) },
				{ string("OFFER_LOOT"),		new Image(string("../Game/Graphics/Images/Actions/OFFER_LOOT.png"),663,26) },
				{ string("REQUEST_LOOT"),	new Image(string("../Game/Graphics/Images/Actions/REQUEST_LOOT.png"),691,26) },
				{ string("THROW_DICE"),		new Image(string("../Game/Graphics/Images/Actions/THROW_DICE.png"),577,24) } };
				//{ string("PLACE_CROW"),		new Image(string("../Game/Graphics/Images/Actions/PLACE_CROW.png"),BUTTON4_XPOS,BUTTON4_YPOS,ACTION_SIZE,ACTION_SIZE) },
				//{ string("CREATE_ALARM"),	new Image(string("../Game/Graphics/Images/Actions/CREATE_ALARM.png"), BUTTON5_XPOS, BUTTON5_YPOS, ACTION_SIZE, ACTION_SIZE) },
				//{ string("SPY_PATROL"),		new Image(string("../Game/Graphics/Images/Actions/SPY_PATROL.png"),BUTTON6_XPOS,BUTTON6_YPOS,ACTION_SIZE,ACTION_SIZE) } };
	for (auto& a : actions)
	{
		a.second->disable();
		hudCont->addObject(a.second);
	}

	//passButton = new Image(string("../Game/Graphics/Images/Actions/PASS.png"), (HUD_WIDTH-ACTION_SIZE)/2,HUD_HEIGHT-ACTION_SIZE, ACTION_SIZE, ACTION_SIZE);
	//hudCont->addObject(passButton);
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
	}
	player1->update();
	player2->update();
}

HudObserver::~HudObserver()
{
	for (auto& a : actions)
		delete a.second;
}
