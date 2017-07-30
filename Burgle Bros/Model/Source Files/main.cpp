#include "../Header Files/GameModel.h"

#include "../../Model/Header Files/Coord.h"
int main(void)
{
	GameModel model;
	model.setBoard();
	
	model.currentPlayer()->setPosition(Coord(0, 0, 0));
	model.currentPlayer()->setName(string("Pepe"));
	model.currentPlayer()->setCharacter(RAVEN);

	model.otherPlayer()->setPosition(Coord(0, 0, 0));
	model.otherPlayer()->setName(string("Gabriela"));
	model.otherPlayer()->setCharacter(PETERMAN);
	int c;

	model.print();
	cin >> c;
	cin >> c;

	model.currentPlayer()->move(model.currentPlayer()->whereCanIMove()[0]);
	model.print();

	model.changeTurn();
	model.currentPlayer()->move(model.currentPlayer()->whereCanIMove()[0]);
	model.print();

	cin >> c;
	cin >> c;

	model.changeTurn();
	model.currentPlayer()->move(model.currentPlayer()->whereCanIMove()[0]);
	model.print();

	cin >> c;
	cin >> c;

	model.changeTurn();
	model.currentPlayer()->move(model.currentPlayer()->whereCanIMove()[0]);
	model.print();

	cin >> c;
	cin >> c;


}