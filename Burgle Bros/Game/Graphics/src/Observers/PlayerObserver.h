#pragma once
#include "./Observer.h"
#include <Player.h>
#include <Configs.h>
#include <alx.hpp>
#include "./BoardObserver.h"
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Text.h"

class PlayerObserver :public Observer
{
public:
	PlayerObserver(Player* p, Container * c, Container* hudCont, Container * boardCont);
	virtual void update()override;
private:
	// Observed object
	Player* player;
	Coord lastPos;
	bool isPlaying;

	pair<int, int> positions[3][4][4];
	//Sound
	alx::Sample * walk;

	// Graphic objects
	Container* parentCont;
	Container* hudCont;
	Image* playerCard;
	Image* lootReverse; // For animation when new loot
	int x0_loot, y0_loot, size0_loot;
	int x1_loot, y1_loot, size1_loot;
	bool lootButtonWithNotif;
	Image * infoButton;
	Image * lootButton;
	Image* characterFigure;
	Image* characterFigurePlaying;
	Image * passButton;
	Image* token;

	Container* loots;
	Text * actionTokens;
	Text * stealthTokens;
	Text * numberOfLoots;
	Text * name;
};