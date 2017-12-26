#include "./FloorObserver.h"

FloorObserver::FloorObserver(Floor* f, Container* boardContainer)
{
	floor = f;
	this->boardContainer = boardContainer;

	floorContainer = new Container(FLOOR_HEIGHT, FLOOR_WIDTH, "Floor " + to_string(floor->number()) + " container");
	floorContainer->setOnlyChildClickable(true);
	floorContainer->setHoverable(false);
	floorContainer->setBorderVisible(true);

	// Set position in board
	switch (floor->number())
	{
	case 0:
		floorContainer->setPosition(FLOOR_YPOS, FLOOR1_XPOS);
		break;
	case 1:
		floorContainer->setPosition(FLOOR_YPOS, FLOOR2_XPOS);
		break;
	case 2:
		floorContainer->setPosition(FLOOR_YPOS, FLOOR3_XPOS);
		break;
	}
	boardContainer->addObject(floorContainer);


	/*
		// Tiles position (Relative to floor)
	#define TILE_A1_XPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_A1_YPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_A2_XPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_A2_YPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_A3_XPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_A3_YPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_A4_XPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_A4_YPOS 3 * ( TILE_SIZE + TILE_SEPARATION )

	#define TILE_B1_XPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_B1_YPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_B2_XPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_B2_YPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_B3_XPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_B3_YPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_B4_XPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_B4_YPOS 3 * ( TILE_SIZE + TILE_SEPARATION )

	#define TILE_C1_XPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_C1_YPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_C2_XPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_C2_YPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_C3_XPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_C3_YPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_C4_XPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_C4_YPOS 3 * ( TILE_SIZE + TILE_SEPARATION )

	#define TILE_D1_XPOS 3 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_D1_YPOS 0 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_D2_XPOS 3 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_D2_YPOS 1 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_D3_XPOS 3 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_D3_YPOS 2 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_D4_XPOS 3 * ( TILE_SIZE + TILE_SEPARATION )
	#define TILE_D4_YPOS 3 * ( TILE_SIZE + TILE_SEPARATION )
			*/
	pair<int, int> tilePositions[4][4];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Floor& fl = *f;
			tiles[i][j] = new TileObserver(fl[i][j], floorContainer);
			tilePositions[i][j] = tiles[i][j]->pos();
		}
	}

	// Attach to floor model
	floor->attach(this);

	deck = new GuardDeckObserver(f,floorContainer,tiles[0][0]->size(), tilePositions);

	guard = new GuardObserver(floor->getGuard(), floorContainer, tiles[0][0]->size(), tilePositions);
}

double FloorObserver::tileSize()
{
	return tiles[0][0]->size();
}
void FloorObserver::update()
{
	//	deck->update();

}