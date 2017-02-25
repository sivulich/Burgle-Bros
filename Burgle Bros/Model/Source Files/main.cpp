#include "../Header Files/GameModel.h"


int main(void)
{
	GameModel model;

	model.setPlayer1Name(string("Robertito"));
	model.setPlayer2Name(string("Elsa"));

	model.startGame();
		
	return 0;
}