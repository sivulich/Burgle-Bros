#include "Guard.h"

Guard::Guard(vector<Coord> floor[4][4], Player * player1, Player * player2)
{
	this->player1 = player1;
	this->player2 = player2;
	for (unsigned i = 0; i < 4; i++)
	{
		for (unsigned j = 0; j < 4; j++) this->floor[i][j] = floor[i][j];
	}
	speed = 2 + floor[1][1].front().floor;
}

Guard::~Guard()
{

}

// guard checks if his current position 
void Guard::GuardCheck()
{
	for (auto &it : player1->getVisibleFrom())
	{
		if (it == pos)
		{
			player1->removeStealthToken();
			break;
		}
	}
	for (auto &it : player2->getVisibleFrom())
	{
		if (it == pos)
		{
			player2->removeStealthToken();
			break;
		}
	}
}

void Guard::FindPath(list<Coord> alarms, Coord dest)
{
	vector<
}

bool Guard::RemoveAlarm(Coord coord)
{
	if (find(alarms.begin(), alarms.end(), coord) != alarms.end())
	{
		alarms.erase(std::remove(alarms.begin(), alarms.end(), coord), alarms.end());
		return true;
	}
	else return false;
}

bool Guard::Move()
{
	if (currsteps > 0)
	{
		/*if (path.empty()) 
		{
			FindPath(alarms, target);
		}*/ //este if creo q esta de mas
		pos = path.front();
		path.pop_front();
		if (pos == target)
		{
			if (patroldeck.isEmpty())
			{
				patroldeck.reset(6);
					speed++;
			}
			patroldeck.discardTop();
			BaseCard * ptr = patroldeck.activeCard();
			PatrolCard * p = static_cast<PatrolCard*>(ptr);
			target = p->getCoord();
			FindPath(alarms, target);
		}
		if(RemoveAlarm(pos))
		{
			FindPath(alarms, target);
		}
		currsteps--;
		return true;
	}
	else return false;
}