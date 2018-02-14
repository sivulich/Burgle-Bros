#include <GameController.h>
#include <GameGraphics.h>
//#include <BurgleNetwork.h>
#include <GameModel.h>
#include "GameState.h"
#include <cstdio>
int main(void)
{
	BurgleNetwork * network = new BurgleNetwork();
	GameModel* model = new GameModel();
	GameGraphics * graphics = new GameGraphics(model);
	GameController game(model, graphics,network);
	while (game.isRunning())
	{
		game.getInput();
		game.processEvent();
	}
	game.stop();
/*
	BurgleNetwork * network = new BurgleNetwork();
	network->connect("127.0.0.1");

	while (!network->join()) {}

	if (network->error())
		cout << network->errMessage() << endl;
	else
	{
		cout << network->isConnected() << endl;
		if (network->isServer())
			network->sendPeek(Coord(0, 0, 0), 1);


		bool b = true;
		while (b)
		{
			remoteInput inp;
			inp.action = NO_TYPE;
			if (network->isServer() == false)
				inp = network->getRemoteInput();
			else
				b = !network->join();
			if (inp.action != NO_TYPE)
			{
				switch (inp.action)
				{
				case ACK:
					cout << "Received an ack " << endl;
					break;
				case MOVE:
					cout << "Received a move! " << endl;
					break;
				case PEEK:
					cout << "Received a peek! " << endl;
					break;
				case ERROR:
					cout << network->errMessage() << endl;
				}
				b = false;
			}
			if (network->error())
			{
				cout << "ERROR: " << network->errMessage() << endl;
				b = false;
			}
		}

	}
	getchar();
	getchar();
	*/
	return 0;
}