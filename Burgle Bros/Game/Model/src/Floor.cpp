#include "./Floor.h"
#include "./ConsoleColors.h"

Tile * Floor::tile(int col, int row)
{
	return tiles[col][row];
};


vector<Tile*>& Floor::operator[] (unsigned i)
{
	return tiles[i];
};


void Floor::setTile(int col, int row, tileType t)
{
	tiles[col][row] = TileFactory().newTile(t, floorNumber, col, row);
	if (t == LASER || t == FINGERPRINT || t == MOTION || t == SCANNER || t == THERMO)
		alarmTiles.push_back(Coord(this->floorNumber, col, row));
};
void Floor::print()
{

	eku::concolinit();
	//	cout << "Floor " << floorNumber + 1 << ":" << endl;
	cout << "__|";
	for (int j = 0; j < 4; j++)
		cout << string(8, '_') << char('A' + j) << string(9, '_') << "|";
	cout << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << " |";
		for (int j = 0; j < 4; j++)
		{
			string name = toString(tiles[j][i]->getType());
			int spaces = 18 - name.length();

			if (guardPos().col == j && guardPos().row == i)
			{
				if (tiles[j][i]->isFlipped())
				{
					cout << eku::green << string(spaces / 2, ' ') + name << eku::blue << "G" << string(spaces - spaces / 2 - 1, ' ') << eku::white;
				}
				else
				{
					cout << eku::red << string(spaces / 2, ' ') + name << eku::blue << "G" << string(spaces - spaces / 2 - 1, ' ') << eku::white;
				}
			}
			else
			{
				if (tiles[j][i]->isFlipped())
				{
					cout << eku::green << string(spaces / 2, ' ') + name + string(spaces - spaces / 2, ' ') << eku::white;
				}
				else
				{
					cout << eku::red << string(spaces / 2, ' ') + name + string(spaces - spaces / 2, ' ') << eku::white;
				}
			}





			if (find(adjacent[j][i].begin(), adjacent[j][i].end(), Coord(floorNumber, j + 1, i)) != adjacent[j][i].end())
				cout << " ";
			else
				cout << "|";
		}
		cout << endl << "  |";
		if (i < 3)
		{
			for (int j = 0; j < 4; j++)
			{
				if (find(adjacent[j][i].begin(), adjacent[j][i].end(), Coord(floorNumber, j, i + 1)) != adjacent[j][i].end())
					cout << "                  ";
				else
					cout << "------------------";
				//cout << "__________________";
				if (j < 3)cout << " ";
			}
			cout << "|" << endl;
		}
		else cout << "__________________ __________________ __________________ __________________|" << endl;
	}
	cout << endl;

}


void Floor::setTiles(vector<tileType> t)
{
	if (t.size() == F_HEIGHT*F_WIDTH)
	{
		for (int j = 0; j < F_HEIGHT*F_WIDTH; j++)
			setTile(j % F_WIDTH, j / F_HEIGHT, t[j]);
	}
	else
	{
		DEBUG_MSG("ERROR: Set tiles received less than 16 tiles");
#ifdef DEBUG
		for (auto& c : t)
			cout << toString(c) << " ";
		cout << endl;
#endif
	}

};

vector<tileType> Floor::getTileSetup()
{
	vector<tileType> v;
	for(int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
			v.push_back(tiles[col][row]->getType());
	}
	return v;
}


int Floor::number()
{
	return floorNumber;
};

bool Floor::moveGuard(PlayerInterface * p)
{
	// Update the list of alarms in the floor
	getAlarms();
	guard.locateGuard();
	if (guard.getCurrSteps() != 0 && tiles[guard.getPos().col][guard.getPos().row]->hasCrowToken())
		guard.decSteps();
	if (!guard.alreadyMoved() && p->getCharacter() == toEnum_characterType("ACROBAT"))
		guard.checkPlayer(p);
	bool ret = guard.move();
	guard.moved(ret);
	tiles[guard.getPos().col][guard.getPos().row]->setAlarm(false);
	return ret;
}

void Floor::setMap(vector<Coord> a[F_WIDTH][F_HEIGHT])
{
	for (int i = 0; i < F_WIDTH; i++)
		for (int j = 0; j < F_HEIGHT; j++)
			adjacent[i][j] = a[i][j];
	guard.setFloorMap(a);
}


void Floor::setStairToken(Coord pos)
{
	stairToken = pos;
}

vector<Coord>& Floor::getAlarms()
{
	alarms.clear();
	for (int i = 0; i < F_WIDTH; i++)
	{
		for (int j = 0; j < F_HEIGHT; j++)
		{
			if (tiles[i][j]->hasAlarm())
				alarms.push_back(Coord(floorNumber, i, j));
		}
	}
	return alarms;
}
// Esta funcion no la usa nadie creo, se agregan las alarmas directamenta al tile
void Floor::addAlarm(Coord c)
{
	tiles[c.col][c.row]->setAlarm(true);
	guard.AddNextAlarm(c);
}

void Floor::getThroughWalls(Coord c, list<Tile*>* adj)
{
	if (c.col < F_WIDTH)
		adj->push_back(tiles[c.row][c.col + 1]);
	if (c.col > 0)
		adj->push_back(tiles[c.row][c.col - 1]);
	if (c.row < F_HEIGHT)
		adj->push_back(tiles[c.row + 1][c.col]);
	if (c.row > 0)
		adj->push_back(tiles[c.row - 1][c.col]);
	return;
}

vector<Coord> Floor::getXDistanceTiles(unsigned x, Coord c)
{
	vector<Coord> v;
	if ((c.col) < 4 && (c.row < 4))
	{
		vector<int> dist(16, INT_MAX);//vector that contains the distance required to go to any point in floor from current pos
		dist[toIndex(c)] = 0;//set distance to current pos = 0
		queue<int> Q;
		Q.push(toIndex(c));
		while (!Q.empty())
		{
			int index = Q.front();
			Q.pop();
			if ((unsigned)dist[index]<x)
			{	
				for (auto &it : adjacent[toCoord(index).col][toCoord(index).row])//search for all adjacents rooms to current one
				{
					if (dist[toIndex(it)] == INT_MAX) //if room was not visited
					{
						Q.push(toIndex(it));//add to queue
						dist[toIndex(it)] = dist[index] + 1;//and set distance equal to distance to parent room + 1
						v.push_back(it);
					}
				}
			}
		}
	}
	return v;
}



Coord Floor::whereToPlaceKitty(Coord const coord)
{
	if ((coord.col) < 4 && (coord.row < 4))
	{
		vector<Coord> visibleAlarms;
		Coord adjTile = NPOS;
		Coord closestATile = NPOS;
		bool here = false;
		for (auto &it : alarmTiles)
		{
			if (tile(it.col, it.row)->isFlipped()) visibleAlarms.push_back(it);
			if (it == coord) here = true;
		}
		if (!here)
		{
			vector<int> dist(16, INT_MAX);//vector that contains the distance required to go to any point in floor from current pos
			vector<int> parent(16, -1);// vector that contains prior room to be accessed following a path from current pos
			dist[toIndex(coord)] = 0;//set distance to current pos = 0
			queue<int> Q;
			Q.push(toIndex(coord));
			while (!Q.empty())
			{
				int index = Q.front();
				Q.pop();
				for (auto &it : adjacent[toCoord(index).col][toCoord(index).row])//search for all adjacents rooms to current one
				{
					if (dist[toIndex(it)] == INT_MAX) //if room was not visited
					{
						Q.push(toIndex(it));//add to queue
						dist[toIndex(it)] = dist[index] + 1;//and set distance equal to distance to parent room + 1
						parent[toIndex(it)] = index;
					}
				}
			}
			if (!visibleAlarms.empty())
			{
				closestATile = toCoord(closestAlarmTile(dist, visibleAlarms));
				if (!(closestATile == NPOS))
				{
					bool b1 = false;
					shortestPath(toIndex(coord), closestAlarmTile(dist, visibleAlarms), parent, &adjTile, &b1);
					return adjTile;
				}
			}
			else
			{
				return NPOS;
			}
		}
		else return coord;
	}
	return NPOS;
}

bool Floor::shortestPath(unsigned const start, unsigned const end, vector<int> parent, Coord * adjTile,bool *b1)
{
	if (start < parent.size() && end < parent.size())//check if end position is inside floor
	{
		if (start == end || end == -1)//if destination and source are the same, target was reached
			*b1 = true;						   //path.push_front(toCoord(start));//es la direccion actual
		else {
			shortestPath(start, parent[end], parent, adjTile,b1);//if destination was not found, try again but with adjacent room from before
			if (*b1 == true)
			{
				*b1 = false;
				*adjTile = toCoord(end);
			}
		}
		return true;
	}
	return false;
}

unsigned Floor::closestAlarmTile(vector<int> distances, vector<Coord> tiles)
{

	unsigned shortDist = INT_MAX;
	unsigned destination = INT_MAX;
	if (tiles.empty() == false)
	{
		for (auto &al : tiles)
		{
			if ((unsigned)distances[toIndex(al)] < shortDist)
			{
				shortDist = distances[toIndex(al)];
				destination = toIndex(al);
			}
		}
	}
	else destination = toIndex(NPOS);
	//DEBUG_MSG(" closest target is in floor " << toCoord(destination) << "\n");
	return destination;
}