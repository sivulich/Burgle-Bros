#include "../Header Files/Guard.h"

Guard::~Guard()
{

}


void Guard::setPlayers(PlayerInterface * p1, PlayerInterface * p2)
{
	player1 = p1;
	player2 = p2; 
}


void Guard::setFloorMap(vector<Coord> floor[4][4])
{
	for (unsigned i = 0; i < 4; i++)
	{
		for (unsigned j = 0; j < 4; j++)
			this->floor[i][j] = floor[i][j];
	}
}

/**
	
*/
void Guard::setDeck(PatrolCardDeck * patroldeck)
{
	this->patroldeck = patroldeck;
	speed = 2 + patroldeck->floor();
};

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
	if (currsteps == 0) SetCurrSteps();
		/*if (path.empty())
		{
		FindPath(pos);
		}*/ //este if creo q esta de mas
		pos = path.front();
		path.pop_front();
		if (pos == target)
		{
			if (patroldeck->isEmpty())
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
		if (currsteps == 0)
			return false;
		else return true;
}


bool Guard::FindPath(Coord const coord)

{
	if ((coord.col) < 4 && (coord.row < 4))
	{
		vector<unsigned> dist(16, 45);
		vector<int> parent(16, -1);
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
		shortestPath(toIndex(coord), closestTarget(dist), parent);
		return true;
	}
	return false;
}

bool Guard::shortestPath(unsigned const start, unsigned const end, vector<int> parent)
{
	if (start < parent.size() && end < parent.size())
	{
		if (start == end || end == -1) {
			//path.push_front(toCoord(start));//es la direccion actual
		}
		else {
			shortestPath(start, parent[end], parent);
			path.push_back(toCoord(end));
		}
		return true;
	}
	return false;
}

unsigned Guard::closestTarget(vector<unsigned> distances)
{

	unsigned closest = distances[toIndex(target)];
	unsigned destination = toIndex(target);
	for (auto& al:alarms)
	{
		if (distances[toIndex(al)] < closest)
		{
			closest = distances[toIndex(al)];
			destination = toIndex(al);

		}//faltaria chequear lo de las izquierdas
	}
	return closest;
}