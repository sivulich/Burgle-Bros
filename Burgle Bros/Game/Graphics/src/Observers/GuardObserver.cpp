#include "./GuardObserver.h"


GuardObserver::GuardObserver(Guard* g, Container* c, double tileSize, pair<int, int> p[4][4])
{
	floor = c;
	guard = g;

	guardIm = new Image(string("./Graphics/Images/Guard.png"));

	guardIm->setSize(tileSize / 2, tileSize / 2);
	//guardIm->setPosition()
	guardIm->setVisible(false);
	guardIm->setClickable(false);
	guardIm->setHoverable(false);
	floor->addObject(guardIm);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			positions[j][i] = pair<int, int>(p[i][j].first + tileSize / 4, p[i][j].second + tileSize / 4);

	dices.resize(7);
	for (int i = 1; i <= 6; i++)
	{
		dices[i] = new Image(string("../View/Images/Dices/White ") + to_string(i) + string(".png"));
		dices[i]->setSize(tileSize / 3, tileSize / 3);

	}

	lastSpeed = g->getSpeed();
	lastPos = NPOS;
	guard->attach(this);
}

void GuardObserver::update()
{
	// Update position
	Coord pos = guard->getPos();
	if (pos != lastPos)
	{
		if (lastPos == NPOS)
		{
			guardIm->setPosition(positions[pos.row][pos.col].first, positions[pos.row][pos.col].second);
			guardIm->setVisible(true);
			floor->addObject(dices[guard->getSpeed()]);
			lastTarget = guard->getTarget();
			std::pair<int, int> p = positions[guard->getTarget().row][guard->getTarget().col];
			dices[lastSpeed]->setPosition(p.first, p.second);
		}
		else
			guardIm->addAnimation(new MoveAnimation(positions[pos.row][pos.col], 0.3));
		lastPos = pos;
	}

	// Update dice
	if (lastSpeed != guard->getSpeed() || lastTarget != guard->getTarget())
	{
		floor->removeObject(dices[lastSpeed]);
		floor->addObject(dices[guard->getSpeed()]);
		std::pair<int, int> p = positions[guard->getTarget().row][guard->getTarget().col];
		dices[lastSpeed]->setPosition(p.first, p.second);

		lastSpeed = guard->getSpeed();
		lastTarget = guard->getTarget();
	}
}

void GuardObserver::reset()
{
	if (guardIm != nullptr)
	{
		floor->removeObject(guardIm);
		floor->addObject(guardIm);
	}
};