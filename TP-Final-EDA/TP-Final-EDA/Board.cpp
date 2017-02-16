#include "Board.h"

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
							  { WALKWAY,         3 }};
	int  i = 6;
	DEBUG_MSG("The file " << i << " is jj" << endl);

	// Fill the vector with the tiles
	vector<tileType> tiles;
	for (auto t:deck)
		for (int i = 0; i < t.second; i++)
			tiles.push_back(t.first);

	// Shuffle it and divide it in three
	random_shuffle(tiles.begin(), tiles.end());

	vector<tileType> f[3];
	for (int i = 0; i < 3; i++)
	{
		f[i].insert(f[i].begin(),tiles.begin() + tiles.size() / 3 * i, tiles.begin() + tiles.size() / 3 * (i + 1));
		f[i].push_back(SAFE);
		f[i].push_back(STAIR);
		random_shuffle(f[i].begin(), f[i].end());

		floor[i] = new Floor(i);
		floor[i]->setTiles(f[i]);
	}
	
}



Board::~Board()
{
	//DESTRUIR  LOS PISOS
}
