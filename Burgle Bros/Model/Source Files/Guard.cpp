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
			this->floor[j][i] = floor[j][i];
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
	if (find(alarms->begin(), alarms->end(), coord) != alarms->end())
	{
		alarms->erase(std::remove(alarms->begin(), alarms->end(), coord), alarms->end());
		DEBUG_MSG("alarm removed from tile "<< coord << "\n");
		return true;
	}
	else
	{
		DEBUG_MSG("there was no alarm in tile " << coord << "\n");
		return false;
	}
}

bool Guard::Move()
{
	BaseCard * ptr;
	PatrolCard * p;
	if (pos == NPOS)
	{
		SetCurrSteps();
		DEBUG_MSG("Current steps " << currsteps<<"\n");
		ptr = patroldeck->next();
		p = static_cast<PatrolCard*>(ptr);
		pos = p->getCoord();
		DEBUG_MSG("Guard start pos "<< pos << "\n");
		ptr = patroldeck->next();
		p = static_cast<PatrolCard*>(ptr);
		//target = p->getCoord();
		//ESTO ES DEBUG
		target = Coord(1, 3, 0);
		DEBUG_MSG("First guard target " << target << "\n");
	}

		FindPath(pos);
		if (pos == target)
		{
			if (patroldeck->isEmpty())
			{
				patroldeck->reset(6);
				speed++;
			}
			ptr = patroldeck->next();
			p = static_cast<PatrolCard*>(ptr);
			target = p->getCoord();
		}
		if (RemoveAlarm(pos))
		{
			FindPath(pos);
		}
		currsteps--;
		if (currsteps == 0)
		{
			DEBUG_MSG("Guard turn has ended\n");
			return false;
		}
		else return true;
}


bool Guard::FindPath(Coord const coord)

{
	if ((coord.col) < 4 && (coord.row < 4))
	{
		vector<int> dist(16, INT_MAX);
		vector<int> parent(16, -1);
		dist[toIndex(coord)] = 0;
		queue<int> Q;
		Q.push(toIndex(coord));
		while (!Q.empty())
		{
			int index = Q.front();
			Q.pop();
			for (auto &it: floor[toCoord(index).col][toCoord(index).row])
			{
				if (dist[toIndex(it)] == INT_MAX) 
				{
					Q.push(toIndex(it));
					dist[toIndex(it)] = dist[index] + 1;
					parent[toIndex(it)] = index;
				}
			}
		}
		shortestPath(toIndex(coord), closestTarget(dist), parent);
		DEBUG_MSG("Distances to each room\n");
		for (auto & a : dist)
			DEBUG_MSG(a << "\n");
		DEBUG_MSG("Room connections from start pos:\n");
		for (auto & a : parent)
			DEBUG_MSG(a << "\n");
		DEBUG_MSG("Path is:\n");
		for (auto& a : path)
			DEBUG_MSG(a << "\n");
		return true;
	}
	return false;
}

bool Guard::shortestPath(unsigned const start, unsigned const end, vector<int> parent)
{
	if (start < parent.size() && end < parent.size())
	{
		if (start == end || end == -1);
			//path.push_front(toCoord(start));//es la direccion actual
		else {
			shortestPath(start, parent[end], parent);
			path.push_back(toCoord(end));
		}
		return true;
	}
	return false;
}

unsigned Guard::closestTarget(vector<int> distances)
{

	unsigned closest = distances[toIndex(target)];
	unsigned destination = toIndex(target);
	for (auto& al: *alarms)
	{
		if (distances[toIndex(al)] < closest)
		{
			closest = distances[toIndex(al)];
			destination = toIndex(al);

		}//faltaria chequear lo de las izquierdas
	}
	DEBUG_MSG(" closest target is in floor " << toCoord(destination) << "\n");
	return closest;
}