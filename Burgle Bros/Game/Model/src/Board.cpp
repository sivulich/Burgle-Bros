#include "./Board.h"

// Defines for the hardcoded map
#define T 0 //Tile
#define W 1 //Wall
#define	´ 0 //No_Wall

Board::Board(PlayerInterface* p1, PlayerInterface* p2)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 3; i++)
		floor[i] = new Floor(i, p1, p2);
}

void Board::setWalls()
{
	// Create the map with the walls
	bool walls[3][(4 * 2) - 1][(4 * 2) - 1] = {
	   {{ T,W,T,´,T,´,T },
		{ ´,´,´,´,W,´,´ },
		{ T,´,T,´,T,W,T },
		{ W,´,W,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,W },
		{ T,W,T,W,T,´,T } },

	   {{ T,W,T,W,T,W,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,W,´,W,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,W,T,W,T,W,T } },

	  { { T,´,T,´,T,´,T },
		{ ´,´,´,´,W,´,´ },
		{ T,W,T,´,T,W,T },
		{ W,´,´,´,W,´,´ },
		{ T,W,T,W,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,W,T } }
	};
	//FLOOR TEMPLATE IF NEW FLOOR CONFIGURATION IS DESIRED
	/*bool walls[3][(4 * 2) - 1][(4 * 2) - 1] = {
	  { { T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T } },

	  { { T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T } },

	  { { T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,´,T } }
	};*/

	for (int f = 0; f < NUMBER_FLOORS; f++)
	{
		for (int row = 0; row < F_HEIGHT; row++)
		{
			for (int col = 0; col < F_WIDTH; col++)
			{
				int i = row * 2;
				int j = col * 2;
				Tile * tile = getTile(Coord(f, col, row));

				// Adjacent with tile above
				if (row > 0 && (walls[f][i - 1][j] != W))
				{
					adjacent[f][col][row].push_back(Coord(f, col, row - 1));
					tile->addAdjacent(Coord(f, col, row - 1));
					tile->setNorthWall(false);
				}
				else tile->setNorthWall(true);
				// Adjacent with tile below
				if (row < 3 && (walls[f][i + 1][j] != W))
				{
					adjacent[f][col][row].push_back(Coord(f, col, row + 1));
					tile->addAdjacent(Coord(f, col, row + 1));
					tile->setSouthWall(false);
				}
				else tile->setSouthWall(true);
				// Adjacent with the left tile
				if (col > 0 && (walls[f][i][j - 1] != W))
				{
					adjacent[f][col][row].push_back(Coord(f, col - 1, row));
					tile->addAdjacent(Coord(f, col - 1, row));
					tile->setWestWall(false);
				}
				else tile->setWestWall(true);
				// Adjacent with the right tile
				if (col < 3 && (walls[f][i][j + 1] != W))
				{
					adjacent[f][col][row].push_back(Coord(f, col + 1, row));
					tile->addAdjacent(Coord(f, col + 1, row));
					tile->setEastWall(false);
				}
				else tile->setEastWall(true);
			}
		}
		//Pass the map to each floor (and each floor to its guard)
		floor[f]->setMap(adjacent[f]);
	}
}

void Board::setBoard()
{
	// The tiles defined by the game
	map<tileType, int> deck = {
		{ ATRIUM,          2 },
		{ CAMERA,          4 },
		{ COMPUTER_ROOM_L, 1 },
		{ COMPUTER_ROOM_M, 1 },
		{ COMPUTER_ROOM_F, 1 },
		{ DEADBOLT,        3 },
		{ FINGERPRINT,     3 },
		{ FOYER,           2 },
		{ KEYPAD,          3 },
		{ LABORATORY,      2 },
		{ LASER,           3 },
		{ LAVATORY,        1 },
		{ MOTION,          3 },
		{ SCANNER,         3 },
		{ SECRET_DOOR,     2 },
		{ SERVICE_DUCT,    2 },
		{ THERMO,          3 },
		{ WALKWAY,         3 } };

	// Fill the vector with the tiles
	vector<tileType> tiles;
	for (auto t : deck)
		for (int i = 0; i < t.second; i++)
			tiles.push_back(t.first);

	// Shuffle it and divide it in three
	random_shuffle(tiles.begin(), tiles.end());

	vector<tileType> f[NUMBER_FLOORS];
	for (int i = 0; i < NUMBER_FLOORS; i++)
	{
		f[i].insert(f[i].begin(), tiles.begin() + tiles.size() / NUMBER_FLOORS * i, tiles.begin() + tiles.size() / NUMBER_FLOORS * (i + 1));
		f[i].push_back(SAFE);
		f[i].push_back(STAIR);
		random_shuffle(f[i].begin(), f[i].end());
		floor[i]->setTiles(f[i]);
		//floor[i]->print();
	}
	parseBoard();

}

void Board::setBoard(vector<tileType> tiles)
{
	//Fills board only if exact number of required tiles is supplied
	if (tiles.size() == F_HEIGHT*F_WIDTH*NUMBER_FLOORS)
	{
		vector<tileType> f[NUMBER_FLOORS];
		for (int i = 0; i < NUMBER_FLOORS; i++)
		{
			f[i].insert(f[i].begin(), tiles.begin() + tiles.size() / NUMBER_FLOORS * i, tiles.begin() + tiles.size() / NUMBER_FLOORS * (i + 1));
			floor[i]->setTiles(f[i]);
		}
	}
}

vector<tileType> Board::getTileSetup()
{
	vector<tileType> tiles;
	for (int i = 0; i < 3; i++)
	{
		vector<tileType> v = floor[i]->getTileSetup();
		tiles.insert(tiles.end(), v.begin(), v.end());
	}
	return tiles;
}

void Board::parseBoard()
{
	vector<Tile *> crackSafeTiles;
	ServiceDuct * duct1 = nullptr;
	ComputerRoomF * computerRoomF = nullptr;
	ComputerRoomM * computerRoomM = nullptr;
	ComputerRoomL * computerRoomL = nullptr;
	vector<Fingerprint *> fingerprints;
	vector<Motion *> motions;
	vector<Laser *> lasers;
	vector<Tile *> safes;

	lootType l[] = { TIARA, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR, GOLD_BAR };
	vector<lootType>loots(l, l + 10);
	random_shuffle(loots.begin(), loots.end());


	// Do some modifications to map because special tiles
	for (int f = 0; f < NUMBER_FLOORS; f++)
	{
		for (int row = 0; row < F_HEIGHT; row++)
		{
			for (int col = 0; col < F_WIDTH; col++)
			{
				Tile * tile = getTile(Coord(f, col, row));

				switch (tile->getType())
				{
				case STAIR:
					// If there is a Stair tile add adjacency with next floor
					if (f < 2)
					{
						getTile(Coord(f + 1, col, row))->addAdjacent(Coord(f, col, row));
						tile->addAdjacent(Coord(f + 1, col, row));
						//floor[f + 1]->setStairToken(Coord(f + 1, col, row));
						getTile(Coord(f + 1, col, row))->setStairToken(true);
					}
					else
						tile->addAdjacent(ROOF);
					break;

				case SAFE:
					//If there is a safe set a loot
					((Safe*)tile)->setLoot(/*loots.back()*/CURSED_GOBLET);
					loots.pop_back();
					prepSafeTile((Safe *)tile);
					safes.push_back(tile);
					if (safes.size() == 3)
					{
						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 3; j++)
							{
								if (i != j)
									((Safe *)safes[i])->addSafe(safes[j]);
							}
						}
					}
					break;

				case SERVICE_DUCT:
					// Find both service ducts and connect them
					if (duct1 == nullptr)
						duct1 = (ServiceDuct*)tile;
					else
					{
						duct1->setOtherSide((ServiceDuct*)tile);
						((ServiceDuct*)tile)->setOtherSide(duct1);
					}
					break;
				case CAMERA:
					cameras.push_back(tile);
					if (cameras.size() == 4)
					{
						for (int i = 0; i < 4; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								if (i != j)
									((Camera *)cameras[i])->addCamera(cameras[j]);
							}
						}
					}
					break;
				case COMPUTER_ROOM_F:
					computerRoomF = (ComputerRoomF *)tile;
					break;
				case COMPUTER_ROOM_L:
					computerRoomL = (ComputerRoomL *)tile;
					break;
				case COMPUTER_ROOM_M:
					computerRoomM = (ComputerRoomM *)tile;
					break;
				case FINGERPRINT:
					fingerprints.push_back((Fingerprint*)tile);
					break;
				case LASER:
					lasers.push_back((Laser*)tile);
					break;
				case MOTION:
					motions.push_back((Motion*)tile);
					break;
				case SECRET_DOOR:
					if (col != 0)	// if its not in the first column	
						((SecretDoor *)tile)->addSecretDoor(getTile(Coord(f, col - 1, row)));
					if (col != 3)	// if its not in the last column
						((SecretDoor *)tile)->addSecretDoor(getTile(Coord(f, col + 1, row)));
					if (row != 0)	// if its not in the first row
						((SecretDoor *)tile)->addSecretDoor(getTile(Coord(f, col, row - 1)));
					if (row != 3)	// if its not in the last row
						((SecretDoor *)tile)->addSecretDoor(getTile(Coord(f, col, row + 1)));
					break;
				}
			}
		}
	}
	for (size_t i = 0; i < 3; i++)
	{
		fingerprints[i]->setComputerRoom(computerRoomF);
		motions[i]->setComputerRoom(computerRoomM);
		lasers[i]->setComputerRoom(computerRoomL);
	}
}


void Board::print()
{
	cout << "                                   |BOARD|" << endl;
	for (int i = 0; i < NUMBER_FLOORS; i++)
		floor[i]->print();

	cout << endl;
	for (int j = 0; j < NUMBER_FLOORS; j++)
	{
		cout << "Alarms in floor " << j + 1 << ":";
		for (auto &a : floor[j]->getAlarms())
			cout << a;
		cout << endl;
	}
}

Tile * Board::getTile(Coord c)
{
	return (*floor[c.floor])[c.col][c.row];
}
Board::~Board()
{
	//DESTRUIR  LOS PISOS!!!
}


void Board::prepSafeTile(Safe * safe) {
	for (int index = 0; index < 4; index++)
	{
		if (index != safe->col())// if index is not the safe's column
			safe->addCrackTile(getTile(Coord(safe->floor(), index, safe->row())));// add the tile in that floor, row and i column
		if (index != safe->row())// if index is not the safe's row
			safe->addCrackTile(getTile(Coord(safe->floor(), safe->col(), index)));// add the tile in that floor, row and i column
	}
}

void Board::checkOnePlayer(PlayerInterface * p, unsigned f)
{
	if (f < 3)
	{
		Coord temp = p->getPosition();
		if (p->has(TIARA))
		{
			if (!(p->getPosition().row == 0) && !this->getTile(p->getPosition())->hasNorthWall())//if its not the first row
				p->addVisibleTile(Coord(temp.floor, temp.col, temp.row - 1));
			if (!(p->getPosition().row == 3) && !this->getTile(p->getPosition())->hasSouthWall())// if its not the last row
				p->addVisibleTile(Coord(temp.floor, temp.col, temp.row + 1));
			if (!(p->getPosition().col == 0) && !this->getTile(p->getPosition())->hasWestWall())// if its not the first column
				p->addVisibleTile(Coord(temp.floor, temp.col - 1, temp.row));
			if (!(p->getPosition().col == 3) && !this->getTile(p->getPosition())->hasEastWall())// if its not the last column
				p->addVisibleTile(Coord(temp.floor, temp.col + 1, temp.row));
		}
		this->floor[f]->getGuard()->checkPlayer(p);
		this->getTile(p->getPosition())->updateVisibleFrom(p);
	};
}

void Board::checkCameras(Coord c1)
{
	if (c1 != ROOF)
	{
		if (floor[c1.floor]->tile(c1.col, c1.row)->is(CAMERA))
		{
			for (unsigned i = 0; i < NUMBER_FLOORS; i++)
			{
				for (auto &it : cameras)
				{
					if (!(floor[i]->getGuard()->getPos() == c1) && floor[i]->getGuard()->getPos() == it->getPos() && floor[c1.floor]->tile(floor[i]->getGuard()->getPos().col, floor[i]->getGuard()->getPos().row)->isFlipped())
						floor[c1.floor]->tile(c1.col, c1.row)->setAlarm(true);
				}
			}
		}
	}
};

void Board::setSilentAlarm(Coord c)
{
	if (c.floor < NUMBER_FLOORS)
	{
		for (unsigned i = 0; i <= c.floor; i++)
		{
			this->getGuard(i)->increaseSpeed();
		}
	}
}