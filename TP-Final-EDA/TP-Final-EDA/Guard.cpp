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

}

bool Guard::Move()
{
	if (currsteps > 0)
	{
		if (path.empty())
		{
			FindPath(alarms, target);
		}
		pos = path.front();
		path.pop_front();
		if (pos == target)
		{
			//saco carta del patroldeck y lo pongo como nuevo target
		}
		if (find(alarms.begin(), alarms.end(), pos) != alarms.end())
		{
			alarms.erase(std::remove(alarms.begin(), alarms.end(), pos), alarms.end());
		}
		currsteps--;
		return true;
	}
	else return false;
	/*
	if (currsteps > 0)
	{
	if (path.empty())
	{

	FindPath(alarms, target);

	}
	pos = path.front();
	path.pop_front();
	currsteps--;
	return true;
	}
	else
	{
	currsteps = speed + alarms.size();//sumar cantidad de merges del mazo
	}*/
}