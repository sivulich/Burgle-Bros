#include "./PlayerObserver.h"
#include <GraphicsDefs.h>
#include "../Animations/MoveAnimation.h"
#include "../Animations/FadeInOutAnimation.h"
#include "../Animations/FadeAnimation.h"
PlayerObserver::PlayerObserver(Player* p, Container * c, Container* h)
{
	player = p;
	parentCont = c;
	hudCont = h;

	// Load player card
	map<characterType, string> images = { { ACROBAT,string("./Graphics/Images/Characters/The Acrobat.png") },
	{ HACKER,string("./Graphics/Images/Characters/The Hacker.png") },
	{ HAWK,string("./Graphics/Images/Characters/The Hawk.png") },
	{ JUICER,string("./Graphics/Images/Characters/The Juicer.png") },
	{ PETERMAN,string("./Graphics/Images/Characters/The Peterman.png") },
	{ RAVEN,string("./Graphics/Images/Characters/The Raven.png") },
	{ SPOTTER,string("./Graphics/Images/Characters/The Spotter.png") } };

	characterFigure = new Image(string("./Graphics/Images/Screen - Game/Characters/") + toString(p->getCharacter()) + string(" 1.png"));
	characterFigurePlaying = new Image(string("./Graphics/Images/Screen - Game/Characters/") + toString(p->getCharacter()) + string(" 1 PLAYING.png"));
	loots = new Container(string("./Graphics/Images/Screen - Game/LootCont.png"));

	if (p->getNumber() == 1)
	{
		playerCard = new Image(images[p->getCharacter()], 128, 488, 168, 186);
		characterFigure->setPosition(525, 130);
		characterFigurePlaying->setPosition(525, 130);
		passButton = new Image(string("./Graphics/Images/HUD/PASS.png"),159,62);
		actionTokens = new Text(string(HUD_FONT), TEXT_COLOR, 15, 195, 70);
		stealthTokens = new Text(string(HUD_FONT), al_map_rgb(0, 0, 0), 15, 212,48);
		numberOfLoots = new Text(string(HUD_FONT), al_map_rgb(0, 0, 0), 15, 255, 62);
		name = new Text(string(HUD_FONT), TEXT_COLOR, 18, 76, 82);
		infoButton = new Image(string("./Graphics/Images/HUD/INFO.png"), 130, 77);
		lootButton = new Image(string("./Graphics/Images/Tokens/Loot token.png"), 233, 46);
		loots->setPosition(409,145);

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
		loots->setPosition(409,675);
	}
	else
		DEBUG_MSG("ERROR: Invalid player number");


	infoButton->setObserver(this);
	hudCont->addObject(infoButton);

	lootButton->setObserver(this);
	hudCont->addObject(lootButton);

	characterFigure->setClickable(false);
	characterFigure->setHoverable(false);
	characterFigurePlaying->setClickable(false);
	characterFigurePlaying->setHoverable(false);

	c->addObject(characterFigure);
	c->addObject(characterFigurePlaying);
	isPlaying = player->isPlaying();
	if (isPlaying)
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
	map<characterType, string> figures = { { ACROBAT,string("./Graphics/Images/Figures/The Acrobat.png") },
	{ HACKER,string("./Graphics/Images/Figures/The Hacker.png") },
	{ HAWK,string("./Graphics/Images/Figures/The Hawk.png") },
	{ JUICER,string("./Graphics/Images/Figures/The Juicer.png") },
	{ PETERMAN,string("./Graphics/Images/Figures/The Peterman.png") },
	{ RAVEN,string("./Graphics/Images/Figures/The Raven.png") },
	{ SPOTTER,string("./Graphics/Images/Figures/The Spotter.png") } };

	token = new Image(figures[player->getCharacter()], 0, 0, TOKEN_WIDTH, TOKEN_HEIGHT);
	token->setVisible(false);
	token->setClickable(false);
	token->setHoverable(false);
	parentCont->addObject(token);
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
				positions[f][r][c] = pair<int, int>(BOARD_YPOS + FLOOR_YPOS + TILE_POS_Y[r][c] + (TILE_SIZE - TOKEN_HEIGHT) / 2, BOARD_XPOS + FLOOR_XPOS[f] + TILE_POS_X[r][c] + XOFFSET);

	//------------------------------------------------------------------------------------


	// Observed variables;
	lastPos = NPOS;
	player->attach(this);

	update();
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
		else
		{
			pair<int, int> target = positions[curr.floor][curr.row][curr.col];
			if (curr.floor != lastPos.floor)
				token->addAnimation(new FadeInOutAnimation(target, TOKEN_MOVE_SPEED * 2));
			else
				token->addAnimation(new MoveAnimation(target, TOKEN_MOVE_SPEED));
		}
		
		lastPos = curr;
	}
	if (player->getName() != name->getText())
	{
		name->setText(player->getName());
	}
	// Update character figure
	if (isPlaying != player->isPlaying())
	{
		isPlaying = player->isPlaying();
		if (isPlaying)
		{
			characterFigure->setVisible(false);
			characterFigurePlaying->setVisible(true);
			actionTokens->setVisible(true);
			passButton->setVisible(true);
			if (player->isThrowingDices()) passButton->setClickable(false);
			else passButton->setClickable(true);
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
		stealthTokens->setText(currentStealthTokens);

	// Update loots
	vector<Loot*> playerLoots = player->getLoots();
	if (numberOfLoots->getText() != to_string(playerLoots.size()))
	{
		numberOfLoots->setText(to_string(playerLoots.size()));
		loots->clear();
		for (unsigned i=0; i< playerLoots.size(); i++)
		{
			Image* image = new Image(string("./Graphics/Images/Loot/") + toString(playerLoots[i]->getType()) + string(".png"), i*162.5, 0,145,145);
			loots->addObject(image);
		}
	}

	playerCard->setVisible(infoButton->isClicked());
	loots->setVisible(lootButton->isClicked());
}