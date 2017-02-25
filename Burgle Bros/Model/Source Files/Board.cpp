#include "../Header Files/Board.h"

// Defines for the hardcoded map
#define T 0
#define W 1
#define	´ 0

Board::Board()
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

	vector<tileType> f[3];
	for (int i = 0; i < 3; i++)
	{
		f[i].insert(f[i].begin(), tiles.begin() + tiles.size() / 3 * i, tiles.begin() + tiles.size() / 3 * (i + 1));
		f[i].push_back(SAFE);
		f[i].push_back(STAIR);
		random_shuffle(f[i].begin(), f[i].end());

		floor[i] = new Floor(4, 4, i);

		for (unsigned int j = 0; j < f[i].size(); j++)
			floor[i]->setTile(j % 4, j / 4, f[i][j]);

		//floor[i]->setTiles(f[i]);
	}

	// Create the map with the walls
	bool walls[3][(4 * 2) - 1][(4 * 2) - 1] = {
		{ { T,W,T,´,T,´,T },
		{ ´,´,´,´,W,´,´ },
		{ T,´,T,´,T,W,T },
		{ W,´,W,´,´,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,W },
		{ T,W,T,W,T,´,T } },

		{ { T,W,T,W,T,W,T },
		{ ´,´,´,´,W,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,W,´,W,´,´ },
		{ T,´,T,´,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,W,T,W,T,W,T } },

		{ { T,´,T,´,T,´,T },
		{ ´,´,´,´,W,´,´ },
		{ T,´,T,´,T,W,T },
		{ W,´,´,´,W,´,´ },
		{ T,W,T,W,T,´,T },
		{ ´,´,´,´,´,´,´ },
		{ T,´,T,´,T,W,T } }
	};
	ServiceDuct* duct1 = nullptr;


	lootType l[] = { TIARA, PERSIAN_KITTY, PAINTING, MIRROR, KEYCARD, ISOTOPE, GEMSTONE, CURSED_GOBLET, CHIHUAHUA, GOLD_BAR, GOLD_BAR };
	vector<lootType>loots(l, l + 10);
	random_shuffle(loots.begin(), loots.end());

	for (int f = 0; f < 3; f++)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				int i = row * 2 + 1;
				int j = col * 2 + 1;
				Tile * tile = (*floor[f])[col][row];

				// If there is a Stair tile add adjacency with next floor
				if (tile->is(STAIR) && f < 2)
				{
					(*floor[f + 1])[col][row]->setAdjacent(Coord(f, col, row));
					tile->setAdjacent(Coord(f + 1, col, row));
					floor[f + 1]->setStairToken(Coord(f + 1, col, row));
				}

				//If there is a safe set a loot
				if (tile->is(SAFE))
				{
					((Safe*)tile)->setLoot(loots.back());
					loots.pop_back();
				}

				// If there is a Service Duct tile
				if (tile->is(SERVICE_DUCT))
				{
					if (duct1 == nullptr)
						duct1 = (ServiceDuct*)tile;
					else
					{
						duct1->setOtherSide((ServiceDuct*)tile);
						((ServiceDuct*)tile)->setOtherSide(duct1);
					}

				}

				// Adjacent with tile above
				if (row > 0 && walls[f][i - 1][j] != W)
				{
					adjacent[f][col][row].push_back(Coord(f, col - 1, row));
					tile->setAdjacent(Coord(f, col - 1, row));
				}
				// Adjacent with tile below
				if (row < 3 && walls[f][i + 1][j] != W)
				{
					adjacent[f][col][row].push_back(Coord(f, col + 1, row));
					tile->setAdjacent(Coord(f, col + 1, row));
				}
				// Adjacent with the left tile
				if (col > 0 && walls[f][i][j - 1] != W)
				{
					adjacent[f][col][row].push_back(Coord(f, col, row - 1));
					tile->setAdjacent(Coord(f, col, row - 1));
				}
				// Adjacent with the right tile
				if (col < 3 && walls[f][i][j + 1] != W)
				{
					adjacent[f][col][row].push_back(Coord(f, col, row + 1));
					tile->setAdjacent(Coord(f, col, row + 1));
				}

			}
		}
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
