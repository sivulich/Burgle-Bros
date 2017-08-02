#include "./BoardObserver.h"

BoardObserver::BoardObserver(Board* b, Container* c)
{
	parent = c;
	board = b;

	for (int i=0;i<3;i++)
		floorContainer[i] = new Container(FLOOR_HEIGHT, FLOOR_WIDTH);

		floorContainer[0]->setPosition(FLOOR_YPOS,FLOOR1_XPOS);
		floorContainer[1]->setPosition(FLOOR_YPOS,FLOOR2_XPOS);
		floorContainer[2]->setPosition(FLOOR_YPOS,FLOOR3_XPOS);

	for (int i = 0; i<3; i++)
		floors[i] = new FloorObserver(&(*b)[i], floorContainer[i]);

	// Add the containers to parent
	for (auto & fl : floorContainer)
		parent->addObject(fl);

	// Atach to the model of the board
	board->attach(this);
}

void BoardObserver::update()
{
	for (auto& f : floors)
		f->update();
}