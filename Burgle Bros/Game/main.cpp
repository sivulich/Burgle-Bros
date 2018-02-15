#include <GameController.h>
#include <GameGraphics.h>
#include <BurgleNetwork.h>
#include <GameModel.h>
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

	/*BurgleNetwork * network = new BurgleNetwork();
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
			remoteInput	inp = network->getRemoteInput();
			if (inp.action != NO_TYPE)
				b = false;
			if (network->error())
			{
				cout << "ERROR: " << network->errMessage() << endl;
				b = false;
			}
		}


		if (network->isServer() == false)
			network->sendMove(Coord(1, 1, 3), 1);
		b = true;
		while (b)
		{
			remoteInput	inp = network->getRemoteInput();
			if (inp.action != NO_TYPE)
				b = false;
			if (network->error())
			{
				cout << "ERROR: " << network->errMessage() << endl;
				b = false;
			}
		}

	}
	getchar();
	getchar();*/
	
	return 0;
}