#include "./LocalPlayerObserver.h"


LocalPlayerObserver::LocalPlayerObserver(Player* p, BoardObserver* bo, Container* pa)
{
	map<characterType, string> images= {	{ ACROBAT,string("../View/Images/Characters/The Acrobat.png")},
										{ HACKER,string("../View/Images/Characters/The Hacker.png") },
										{ HAWK,string("../View/Images/Characters/The Hawk.png") },
										{ JUICER,string("../View/Images/Characters/The Juicer.png") },
										{ PETERMAN,string("../View/Images/Characters/The Peterman.png") },
										{ RAVEN,string("../View/Images/Characters/The Raven.png") },
										{ SPOTTER,string("../View/Images/Characters/The Spotter.png") } };

	map<characterType,string> figures= {	{ ACROBAT,string("../View/Images/Figures/The Acrobat.png")},
										{ HACKER,string("../View/Images/Figures/The Hacker.png") },
										{ HAWK,string("../View/Images/Figures/The Hawk.png") },
										{ JUICER,string("../View/Images/Figures/The Juicer.png") },
										{ PETERMAN,string("../View/Images/Figures/The Peterman.png") },
										{ RAVEN,string("../View/Images/Figures/The Raven.png") },
										{ SPOTTER,string("../View/Images/Figures/The Spotter.png") } };
	board = bo;
	player = p;
	parent = pa;
	hud = new Container(string("../View/Images/hudTest.png"));
	hud->setScale(double(pa->getWidth()) / hud->getWidth());
	hud->setPosition(pa->getHeight() - hud->getScale()*hud->getHeight(), 0);
	playerCard = new Image(images[p->getCharacterType()]);
	playerCard->setPosition(100,30);
	playerCard->setScale(0.7*double(hud->getHeight()) / playerCard->getHeight());
	hud->addObject(playerCard);
	
	parent->addObject(hud);
	token = new Image(figures[player->getCharacterType()]);
	BoardObserver& b = *board;
	token->setScale(0.9*  0.8*b[0].getFloorGrid()->getHeight() / 4/token->getHeight());
	player->attach(this);

	Coord pos = player->getPosition();
	b[pos.floor].getFloorGrid()->addObject(token);
	token->setPosition(pos.row*b[pos.floor].getFloorGrid()->getWidth() / 4 + 0.9 * b[pos.floor].getFloorGrid()->getWidth() / 4-token->getScale()*token->getHeight(), pos.col*b[pos.floor].getFloorGrid()->getWidth() / 4 +0.45* b[pos.floor].getFloorGrid()->getWidth() / 4-token->getScale()/2.0*token->getWidth());
	actions = new ActionObserver(p, 20, 5, hud);
	update();
}
void
LocalPlayerObserver::update() {
	BoardObserver& b = *board;
	Coord pos = player->getPosition();
	for (int i = 0; i < 3; i++)
	{
		if (i != pos.floor)
		{
			if (b[i].getFloorGrid()->contains(token) == true)
				b[i].getFloorGrid()->removeObject(token);
		}
		else
		{
			b[i].getFloorGrid()->removeObject(token);
			b[i].getFloorGrid()->addObject(token);
			pair<int, int> target(pos.row*b[pos.floor].getFloorGrid()->getWidth() / 4 + 0.9 * b[pos.floor].getFloorGrid()->getWidth() / 4 - token->getScale()*token->getHeight(), pos.col*b[pos.floor].getFloorGrid()->getWidth() / 4 + 0.45* b[pos.floor].getFloorGrid()->getWidth() / 4 - token->getScale() / 2.0*token->getWidth());
			if(token->hasAnimation() ==false ||  ((MoveAnimation*)token->getAnimation())->getTarget()!=target )
				token->addAnimation(new MoveAnimation(token->getPos(), target, 0.2));
		}
	}
	actions->update();
}