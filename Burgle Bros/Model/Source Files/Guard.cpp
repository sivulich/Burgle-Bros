#include "../Header Files/Guard.h"

Guard::Guard(vector<Coord> floor[4][4], Player * player1, Player * player2, PatrolCardDeck * patroldeck)
{
	this->player1 = player1;
	this->player2 = player2;
	this->patroldeck = patroldeck;
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
		FindPath(pos);
		}*/ //este if creo q esta de mas
		pos = path.front();
		path.pop_front();
		if (pos == target)
		{
			if (patroldeck->isEmpty)
			{
				patroldeck->reset(6);
				speed++;
			}
			patroldeck->discardTop();
			BaseCard * ptr = patroldeck->activeCard();
			PatrolCard * p = static_cast<PatrolCard*>(ptr);
			target = p->getCoord();
			FindPath(pos);
		}
		if (RemoveAlarm(pos))
		{
			FindPath(pos);
		}
		currsteps--;
		return true;
	}
	else return false;
}


void Guard::FindPath(Coord const coord)
{

	int *dist = new int[16];
	int *parent = new int[16];

	for (int v = 0; v < 16; ++v)
	{
		dist[v] = 45;
		parent[v] = -1;
	}
	dist[toIndex(coord)] = 0;
	queue<int> Q;
	Q.push(toIndex(coord));

	while (!Q.empty())
	{
		int index = Q.front();
		Q.pop();
		vector<Coord>::iterator it;

		for (it = floor[toCoord(index).col][toCoord(index).row].begin(); it != floor[toCoord(index).col][toCoord(index).row].end(); ++it)
		{
			if (dist[toIndex(*it)] == 45) {
				Q.push(toIndex(*it));
				dist[toIndex(*it)] = dist[index] + 1;
				parent[toIndex(*it)] = index;
			}
		}
	}
	shortestPath(toIndex(coord), closest(), parent);
	delete dist, parent;
}

void Guard::shortestPath(int const &start, int const &end, int* parent)
{
	if (start == end || end == -1) {
		//path.push_front(toCoord(start));//es la direccion actual
	}
	else {
		shortestPath(start, parent[end], parent);
		path.push_back(toCoord(end));
	}
}

unsigned Guard::closest(unsigned * distances)
{
	list<Coord>::iterator it;
	unsigned closest = distances[toIndex(target)];
	unsigned destination = toIndex(target);
	for (it = alarms.begin(); it != alarms.end(); it++)
	{
		if (distances[toIndex(*it)] < closest)
		{
			closest = distances[toIndex(*it)];
			destination = toIndex(*it);

		}//faltaria chequear lo de las izquierdas
	}
	return closest;
}