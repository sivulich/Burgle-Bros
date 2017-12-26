#include "./BoardObserver.h"

BoardObserver::BoardObserver(Board* b, Container* c)
{
	parent = c;
	board = b;
	// Create board container
	boardContainer = new Container(BOARD_HEIGHT, BOARD_WIDTH, "Board Container");
	boardContainer->setPosition(BOARD_YPOS, BOARD_XPOS);
	boardContainer->setBackground(string("../Game/Graphics/Images/Board.jpg"));
	boardContainer->setBorderVisible(true);
	parent->addObject(boardContainer);

	for (int i = 0; i<3; i++)
		floors[i] = new FloorObserver(&(*b)[i], boardContainer);

	// Atach to the model of the board
	board->attach(this);
}

void BoardObserver::update()
{
	for (auto& f : floors)
		f->update();
}