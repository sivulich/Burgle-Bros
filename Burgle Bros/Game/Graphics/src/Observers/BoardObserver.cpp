#include "./BoardObserver.h"

BoardObserver::BoardObserver(GameModel* model, Container* c)
{
	parent = c;
	board = model->getBoard();

	// Create board container
	boardContainer = new Container(BOARD_HEIGHT, BOARD_WIDTH, "Board Container");
	boardContainer->setPosition(BOARD_YPOS, BOARD_XPOS);
	boardContainer->setBackground(string("../Game/Graphics/Images/Board.jpg"));
	parent->addObject(boardContainer);

	for (int i = 0; i<3; i++)
		floors[i] = new FloorObserver(&(*board)[i], boardContainer);

	// Atach to the model of the board
	board->attach(this);
}

void BoardObserver::update()
{
	for (auto& f : floors)
		f->update();
}