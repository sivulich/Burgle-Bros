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

	if (p->getNumber() == 1)
	{
		playerCard = new Image(images[p->getCharacter()], PLAYER1_CARD_XPOS, PLAYER1_CARD_YPOS, PLAYER_CARD_SIZE, PLAYER_CARD_SIZE);
		actionTokens = new Text(string(HUD_FONT), TEXT_COLOR, HUD_FONT_SIZE, PLAYER1_ACTION_TOK_XPOS, PLAYER1_ACTION_TOK_YPOS);
		stealthTokens = new Text(string(HUD_FONT), TEXT_COLOR, HUD_FONT_SIZE, PLAYER1_STEALTH_TOK_XPOS, PLAYER1_STEALTH_TOK_YPOS);
		name = new Text(string(HUD_FONT), TEXT_COLOR, HUD_FONT_SIZE, PLAYER1_STEALTH_TOK_XPOS, PLAYER1_STEALTH_TOK_YPOS + 25);
	}
	else if (p->getNumber() == 2)
	{
		playerCard = new Image(images[p->getCharacter()], PLAYER2_CARD_XPOS, PLAYER2_CARD_YPOS, PLAYER_CARD_SIZE, PLAYER_CARD_SIZE);
		actionTokens = new Text(string(HUD_FONT), TEXT_COLOR, HUD_FONT_SIZE, PLAYER2_ACTION_TOK_XPOS, PLAYER2_ACTION_TOK_YPOS);
		stealthTokens = new Text(string(HUD_FONT), TEXT_COLOR, HUD_FONT_SIZE, PLAYER2_STEALTH_TOK_XPOS, PLAYER2_STEALTH_TOK_YPOS);
		name = new Text(string(HUD_FONT), TEXT_COLOR, HUD_FONT_SIZE, PLAYER2_STEALTH_TOK_XPOS, PLAYER2_STEALTH_TOK_YPOS + 25);
	}
	else
		DEBUG_MSG("ERROR: Invalid player number");
	playerCard->setClickable(false);
	playerCard->setHoverable(false);
	hudCont->addObject(playerCard);

	hudCont->addObject(actionTokens);
	hudCont->addObject(stealthTokens);
	name->setText(p->getName());
	hudCont->addObject(name);
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

	// Update action tokens
	string currentActionTokens = to_string(player->getActionTokens());
	if (actionTokens->getText() != currentActionTokens)
		actionTokens->setText(currentActionTokens);

	// Update stealth tokens
	string currentStealthTokens = to_string(player->getStealthTokens());
	if (stealthTokens->getText() != currentStealthTokens)
		stealthTokens->setText(currentStealthTokens);

}