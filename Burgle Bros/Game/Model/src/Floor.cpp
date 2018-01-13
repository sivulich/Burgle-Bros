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
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 4; row++)
			v[row * 4 + col] = tiles[col][row]->getType();
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

