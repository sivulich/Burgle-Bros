#include "../Header Files/GameModel.h"

#include "../../Model/Header Files/Coord.h"
int main(void)
{/*
	GameModel model;
	model.player1.setPosition(Coord(0, 0, 0));
	model.player1.setName(string("Pepe"));
	model.player1.setCharacter(RAVEN);

	model.player2.setPosition(Coord(0, 0, 0));
	model.player2.setName(string("Gabriela"));
	model.player2.setCharacter(PETERMAN);

	string s1;

	model.print();
	while (1)
	{

		cin >> s1;
		model.input(s1);
		model.runStep();
		model.print();
	}
	return 0;*/
	Board b;
	b.print();
	b[1]->addAlarm(Coord(1, 2, 3));
	while(b[1]->getGuard()->Move());
	while (1);
}