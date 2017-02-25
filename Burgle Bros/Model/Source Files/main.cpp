#include "../Header Files/GameModel.h"

#include "../../Model/Header Files/Coord.h"
int main(void)
{
	GameModel model;

	model.player1.setName(string("Robertito"));
	model.player2.setName(string("Elsa"));

	
	Coord c(1, 4, 5);

	cout << c << endl;
	return 0;
}