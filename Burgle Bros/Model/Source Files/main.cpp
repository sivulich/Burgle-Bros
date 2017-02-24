#include "../Header Files/GameModel.h"


int main(void)
{
	GameModel model;

	model.setPlayer1Name("Robertito");
	model.setPlayer2Name("Elsa");

	model.startGame();
		
	return 0;
}