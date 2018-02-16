#include "./PlayerObserver.h"
#include <GraphicsDefs.h>
#include "./Animations.h"
#include "./DialogBox.h"
PlayerObserver::PlayerObserver(Player* p, Container * c, Container* h, Container * boardCont)
{
	player = p;
	parentCont = c;
	hudCont = h;

	// Load player card
	map<characterType, string> images = { { ACROBAT,string("./Graphics/Images/Characters/ACROBAT.png") },
	{ HACKER,string("./Graphics/Images/Characters/HACKER.png") },
	{ HAWK,string("./Graphics/Images/Characters/HAWK.png") },
	{ JUICER,string("./Graphics/Images/Characters/JUICER.png") },
	{ PETERMAN,string("./Graphics/Images/Characters/PETERMAN.png") },
	{ RAVEN,string("./Graphics/Images/Characters/RAVEN.png") },
	{ SPOTTER,string("./Graphics/Images/Characters/SPOTTER.png") },
	{ NO_CHARACTER_TYPE,string("./Graphics/Images/Characters/NO_CHARACTER_TYPE.png") } };

	characterFigure = new Image(string("./Graphics/Images/Screen - Game/Characters/") + toString(p->getCharacter()) + string(" 1.png"));
	characterFigurePlaying = new Image(string("./Graphics/Images/Screen - Game/Characters/") + toString(p->getCharacter()) + string(" 1 PLAYING.png"));
	loots = new Container(string("./Graphics/Images/Screen - Game/LootCont.png"));



	if (p->getNumber() == 1)
	{
		playerCard = new Image(images[p->getCharacter()], 128, 488, 168, 186);
		characterFigure->setPosition(525, 130);
		characterFigurePlaying->setPosition(525, 130);
		passButton = new Image(string("./Graphics/Images/HUD/PASS.png"), 159, 62);
		actionTokens = new Text(string(HUD_FONT), TEXT_COLOR, 15, 195, 70);
		stealthTokens = new Text(string(HUD_FONT), al_map_rgb(0, 0, 0), 15, 212, 48);
		numberOfLoots = new Text(string(HUD_FONT), al_map_rgb(0, 0, 0), 15, 255, 62);
		name = new Text(string(HUD_FONT), TEXT_COLOR, 18, 76, 82);
		infoButton = new Image(string("./Graphics/Images/HUD/INFO.png"), 130, 77);
		lootButton = new Image(string("./Graphics/Images/Tokens/Loot token.png"), 233, 46);
		loots->setPosition(409, 145);
		x0_loot = 303;
		y0_loot = 409;
		size0_loot = 145;
		x1_loot = 356;
		y1_loot = 644;
		size1_loot = 30;

	}
	else if (p->getNumber() == 2)
	{
		playerCard = new Image(images[p->getCharacter()], 984, 488, 168, 186);
		characterFigure->setPosition(525, 1025);
		characterFigure->flipHorizontal();
		characterFigurePlaying->setPosition(525, 1025);
		characterFigurePlaying->flipHorizontal();
		passButton = new Image(string("./Graphics/Images/HUD/PASS.png"), 807, 62);
		actionTokens = new Text(string(HUD_FONT), TEXT_COLOR, 15, 843, 70);
		stealthTokens = new Text(string(HUD_FONT), al_map_rgb(0, 0, 0), 15, 830, 48);
		numberOfLoots = new Text(string(HUD_FONT), al_map_rgb(0, 0, 0), 15, 793, 62);
		name = new Text(string(HUD_FONT), TEXT_COLOR, 18, 969, 82);
		infoButton = new Image(string("./Graphics/Images/HUD/INFO.png"), 889, 77);
		lootButton = new Image(string("./Graphics/Images/Tokens/Loot token.png"), 771, 46);
		loots->setPosition(409, 675);
		x0_loot = 832;
		y0_loot = 409;
		size0_loot = 145;
		x1_loot = 894;
		y1_loot = 644;
		size1_loot = 30;
	}
	else
		DEBUG_MSG("ERROR: Invalid player number");

	numberOfLoots->setText(string("0"));

	lootReverse = new Image(string("./Graphics/Images/Loot/Loot - Reverse.png"), x0_loot, y0_loot, size0_loot, size0_loot);
	lootReverse->setClickable(false);
	lootReverse->setHoverable(false);
	lootReverse->setVisible(false);
	parentCont->addObject(lootReverse);


	infoButton->setObserver(this);
	hudCont->addObject(infoButton);

	lootButton->setObserver(this);
	lootButtonWithNotif = false;
	hudCont->addObject(lootButton);

	characterFigure->setClickable(false);
	characterFigure->setHoverable(false);
	characterFigurePlaying->setClickable(false);
	characterFigurePlaying->setHoverable(false);

	c->addObject(characterFigure);
	c->addObject(characterFigurePlaying);


	isPlaying_ = player->isPlaying();
	if (isPlaying_)
	{
		characterFigure->setVisible(false);
		actionTokens->setVisible(true);
		passButton->setVisible(true);
	}
	else
	{
		characterFigurePlaying->setVisible(false);
		actionTokens->setVisible(false);
		passButton->setVisible(false);
	}
	if (p->isRemote() == false)
		hudCont->addObject(passButton);
	hudCont->addObject(actionTokens);
	hudCont->addObject(stealthTokens);
	hudCont->addObject(numberOfLoots);

	name->setText(p->getName());
	hudCont->addObject(name);


	playerCard->setClickable(false);
	playerCard->setHoverable(false);
	playerCard->setVisible(false);
	c->addObject(playerCard);

	loots->setClickable(false);
	loots->setHoverable(false);
	loots->setVisible(false);
	c->addObject(loots);

	//------------------------------------------------------------------------------------

	// Load player token
	map<characterType, string> figures = { { ACROBAT,string("./Graphics/Images/Figures/ACROBAT.png") },
	{ HACKER,string("./Graphics/Images/Figures/HACKER.png") },
	{ HAWK,string("./Graphics/Images/Figures/HAWK.png") },
	{ JUICER,string("./Graphics/Images/Figures/JUICER.png") },
	{ PETERMAN,string("./Graphics/Images/Figures/PETERMAN.png") },
	{ RAVEN,string("./Graphics/Images/Figures/RAVEN.png") },
	{ SPOTTER,string("./Graphics/Images/Figures/SPOTTER.png") },
	{ NO_CHARACTER_TYPE,string("./Graphics/Images/Figures/NO_CHARACTER_TYPE.png") } };

	token = new Image(figures[player->getCharacter()], 0, 0, TOKEN_WIDTH, TOKEN_HEIGHT);
	token->setVisible(false);
	token->setClickable(false);
	token->setHoverable(false);
	//parentCont->addObject(token);
	boardCont->addObject(token);
	//------------------------------------------------------------------------------------

	// Compute player token positions
	int XOFFSET;
	if (p->getNumber() == 1)
		XOFFSET = TOKEN_SEPARATION;
	else if (p->getNumber() == 2)
		XOFFSET = TILE_SIZE - TOKEN_WIDTH - TOKEN_SEPARATION;

	for (int f = 0; f < 3; f++)
		for (int r = 0; r < 4; r++)
			for (int c = 0; c < 4; c++)
				//	positions[f][r][c] = pair<int, int>((int)(BOARD_YPOS + FLOOR_YPOS + TILE_YPOS[r][c] + (TILE_SIZE - TOKEN_HEIGHT) / 2), (int)(BOARD_XPOS + FLOOR_XPOS[f] + TILE_XPOS[r][c] + XOFFSET));
				positions[f][r][c] = pair<int, int>((int)(FLOOR_YPOS + TILE_YPOS[r][c] + (TILE_SIZE - TOKEN_HEIGHT) / 2), (int)(FLOOR_XPOS[f] + TILE_XPOS[r][c] + XOFFSET));

	//------------------------------------------------------------------------------------


	// Observed variables;
	lastPos = NPOS;
	player->attach(this);
	walk = new alx::Sample("../Game/Sound/WALK.wav");
	hurt = new alx::Sample("../Game/Sound/HURT.wav");
	update();
}

PlayerObserver::~PlayerObserver()
{
	loots->clear();
	delete loots;

	delete characterFigure;
	delete characterFigurePlaying;
	delete playerCard;
	delete passButton;
	delete actionTokens;
	delete stealthTokens;
	delete numberOfLoots;
	delete name;
	delete infoButton;
	delete lootButton;
	delete lootReverse;
	delete token;
	delete walk;
}


void PlayerObserver::loadPlayerToken(string s)
{
	if (s == "ROMA" || s == "MARCOS" || s == "TOBI" || s == "SANTI" || s == "AGUSTIN" || s == "MARK")
		token->load(string("./Graphics/Images/Figures/") + s + string(".png"));
	else if (s == "RESET")
		token->load(string("./Graphics/Images/Figures/") + string(toString(player->getCharacter())) + string(".png"));
}


void PlayerObserver::update()
{
	// Update player token position
	Coord curr = player->getPosition();
	if (curr != lastPos)
	{
		if (lastPos == NPOS)
		{
			int x = positions[curr.floor][curr.row][curr.col].second;
			int y = positions[curr.floor][curr.row][curr.col].first;
			token->setPosition(y, x);
			token->setAlpha(0.0);
			token->setVisible(true);
			token->addAnimation(new FadeAnimation(0.0, 1.0, 1));
		}
		else if (curr == ROOF)
		{
			token->addAnimation(new FadeAnimation(1.0, 0.0, 1, true));
			characterFigurePlaying->setVisible(false);
			characterFigure->setVisible(true);
			characterFigure->disable();
		}
		else
		{
			pair<int, int> target = positions[curr.floor][curr.row][curr.col];
			if (curr.floor != lastPos.floor)
				token->addAnimation(new FadeInOutAnimation(target, TOKEN_MOVE_SPEED * 2));
			else
				token->addAnimation(new MoveAnimation(target, TOKEN_MOVE_SPEED));
			walk->play(0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE);
		}

		lastPos = curr;
	}

	if (player->getName() != name->getText())
	{
		name->setText(player->getName());
	}

	// Check if character changed
	if (player->getCharacter() != toEnum_characterType(token->getName().c_str()))
	{
		characterFigure->load(string("./Graphics/Images/Screen - Game/Characters/") + toString(player->getCharacter()) + string(" 1.png"));
		characterFigurePlaying->load(string("./Graphics/Images/Screen - Game/Characters/") + toString(player->getCharacter()) + string(" 1 PLAYING.png"));
		token->load(string("./Graphics/Images/Figures/") + toString(player->getCharacter()) + string(".png"));
	}

	// Update character figure
	if (isPlaying_ != player->isPlaying())
	{
		isPlaying_ = player->isPlaying();
		if (isPlaying_)
		{
			characterFigure->setVisible(false);
			characterFigurePlaying->setVisible(true);
			actionTokens->setVisible(true);
			// Hide pass button when player is remote
			if (player->isRemote())
				passButton->setVisible(false);
			else
				passButton->setVisible(true);
		}
		else
		{
			characterFigure->setVisible(true);
			characterFigurePlaying->setVisible(false);
			actionTokens->setVisible(false);
			passButton->setVisible(false);

		}
	}
	// Update action tokens
	string currentActionTokens = to_string(player->getActionTokens());
	if (actionTokens->getText() != currentActionTokens)
		actionTokens->setText(currentActionTokens);

	// Update stealth tokens
	string currentStealthTokens = to_string(player->getStealthTokens());
	if (stealthTokens->getText() != currentStealthTokens)
	{
		//	cout << currentStealthTokens << endl;
			//if (currentStealthTokens == string("-1"))
				//currentStealthTokens = string("0");
		if(currentStealthTokens!="3")
			hurt->play(1, 0, 1, ALLEGRO_PLAYMODE_ONCE);
		stealthTokens->setText(currentStealthTokens);
	}

	// Update loots
	vector<Loot*> playerLoots = player->getLoots();
	int prevNLoots = stoi(numberOfLoots->getText());
	int currNLoots = playerLoots.size();
	if (prevNLoots != currNLoots)
	{
		// A new LOOT
		if (currNLoots > prevNLoots)
		{
			//Animation for new loot
			lootReverse->setPosition(y0_loot, x0_loot);
			lootReverse->setScale(1.0);
			lootReverse->setVisible(true);
			lootReverse->addAnimation(new MoveAndZoomAnimation(x1_loot, y1_loot, size1_loot, size1_loot, 0.5, true));
			lootButton->load(string("./Graphics/Images/Tokens/Loot token with notif.png"));
			lootButtonWithNotif = true;
			//loots->clear();
			for (unsigned i = 0; i < playerLoots.size(); i++)
			{
				if (loots->contains(toString(playerLoots[i]->getType())) == false)
				{
					Image* image = new Image(string("./Graphics/Images/Loot/") + toString(playerLoots[i]->getType()) + string(".png"), i*162.5, 0, 145, 145);
					loots->addObject(image);
					string message;

					switch (playerLoots[i]->getType())
					{
					case TIARA:
						message = string("You got a Tiara! When you move to a tile adjacent to the guard, you lose a stealth token. Moving to the guard's tile removes an extra token.");
						break;
					case PERSIAN_KITTY:
						message = string("You got a Persian Kitty! Every turn you carry it throw a die. The cat will run away if you get a 1 or a 2. Go catch him...");
						break;
					case PAINTING:
						message = string("You got a Painting! You cannot use the special movement features of the Secret Door or Service Duct while carrying it.");
						break;
					case MIRROR:
						message = string("You got a Mirror! Carrying it consumes one action token. On the bright side, you do not trigger an alarm in Laser tiles.");
						break;
					case KEYCARD:
						message = string("You got a Keycard! Now the player holding this MUST be in the Safe tile in order to crack the safe.");
						break;
					case ISOTOPE:
						message = string("You got an Isotope! You will trigger every Thermo alarm while holding this.");
						break;
					case GEMSTONE:
						message = string("You got a Gemstone! Now you spend an extra action token when moving to the same tile as the other player.");
						break;
					case CURSED_GOBLET:
						message = string("You got a Cursed Goblet! You lose a Stealth token.");
						break;
					case CHIHUAHUA:
						message = string("You got a Chihuahua! At the begginning of your turn roll a die. If a 6, the Chihuahua starts barking and sets off an alarm on your tile.");
						break;
					case GOLD_BAR:
						message = string("You got a Gold Bar! Actually two, but you are strong enough to carry only one...");
						break;
					}
					if (player->lastAction() != string("OFFER_LOOT") && player->lastAction() != string("REQUEST_LOOT"))
						DialogBox * b = new DialogBox(DialogBox::OK_MSG, message, parentCont, false);
				}
			}
		}
		else // LOST A LOOT, so update all images
		{
			loots->clear();
			for (unsigned i = 0; i < playerLoots.size(); i++)
				loots->addObject(new Image(string("./Graphics/Images/Loot/") + toString(playerLoots[i]->getType()) + string(".png"), i*162.5, 0, 145, 145));
		}
		numberOfLoots->setText(to_string(currNLoots));
	}

	playerCard->setVisible(infoButton->isClicked());
	loots->setVisible(lootButton->isClicked());
	if (lootButton->isClicked() && lootButtonWithNotif == true)
	{
		lootButton->load(string("./Graphics/Images/Tokens/Loot token.png"));
		lootButtonWithNotif = false;
	}
}