#include "../../Header Files/Observers/LocalPlayerObserver.h"


map<characterType, string> images= {	{ ACROBAT,string("../View/Images/Characters/The Acrobat.png")},
										{ HACKER,string("../View/Images/Characters/The Hacker.png") },
										{ HAWK,string("../View/Images/Characters/The Hawk.png") },
										{ JUICER,string("../View/Images/Characters/The Juicer.png") },
										{ PETERMAN,string("../View/Images/Characters/The Peterman.png") },
										{ RAVEN,string("../View/Images/Characters/The Raven.png") },
										{ SPOTTER,string("../View/Images/Characters/The Spotter.png") } };
LocalPlayerObserver::LocalPlayerObserver(Player* p, BoardObserver* bo, Container* pa)
{
	board = bo;
	player = p;
	parent = pa;
	hud = new Container(string("../View/Images/hudTest.png"));
	hud->setScale(double(pa->getWidth()) / hud->getWidth());
	//hud = new Container(pa->getHeight() *9.0 / 30.0, pa->getWidth());
	//hud->setPosition(pa->getHeight() *21.0 / 30.0, 0);
	hud->setPosition(pa->getHeight() - hud->getScale()*hud->getHeight(), 0);
	playerCard = new Image(images[p->getCharacterType()]);
	playerCard->setPosition(100,30);
	playerCard->setScale(0.7*double(hud->getHeight()) / playerCard->getHeight());
	hud->addObject(playerCard);
	
	parent->addObject(hud);
	token = new Image(string("../View/Images/char.png"));
	BoardObserver& b = *board;
	token->setScale(0.9* 2.0 / 3.0*b[0].getFloorGrid()->getHeight() / 4/token->getHeight());
	player->attach(this);

	Coord pos = player->getPosition();
	b[pos.floor].getFloorGrid()->addObject(token);
	token->setPosition(pos.row*b[pos.floor].getFloorGrid()->getWidth() / 4 + 0.9* 1.0 / 3.0* b[pos.floor].getFloorGrid()->getWidth() / 4, pos.col*b[pos.floor].getFloorGrid()->getWidth() / 4);
	actions = new ActionObserver(p, 20, 5, hud);

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
			pair<int, int> target(pos.row*b[i].getFloorGrid()->getWidth() / 4 + 0.9* 1.0 / 3.0* b[i].getFloorGrid()->getWidth() / 4, pos.col*b[i].getFloorGrid()->getWidth() / 4);
			if(token->hasAnimation() ==false ||  ((MoveAnimation*)token->getAnimation())->getTarget()!=target )
				token->addAnimation(new MoveAnimation(token->getPos(), target, 0.4));
		}
	}
	actions->update();
}