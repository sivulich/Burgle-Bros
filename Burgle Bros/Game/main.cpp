#include <GameController.h>
#include <GameGraphics.h>
#include <BurgleNetwork.h>
#include <GameModel.h>
#include <cstdio>
int main(void)
{
	GameGraphics * graphics = new GameGraphics();
	GameController game( graphics);
	while (game.isRunning())
	{
		game.getInput();
		game.processEvent();
	}
	game.stop();

	//BurgleNetwork * network = new BurgleNetwork();
	//network->connect("127.0.0.1");

	//while (!network->join()) {}

	//if (network->error())
	//	cout << network->errMessage() << endl;
	//else
	//{
	//	if (network->isServer())
	//		network->sendPeek(Coord(0, 0, 0), 1);

	//	bool b = true;
	//	while (b)
	//	{
	//		remoteInput	inp = network->getRemoteInput();
	//		if (inp.action != NO_TYPE)
	//		{
	//			b = false;
	//			//cout << "Received a " << inp.action << endl;
	//		}
	//			
	//		if (network->error())
	//		{
	//			cout << "ERROR: " << network->errMessage() << endl;
	//			b = false;
	//		}
	//	}

	//	if (network->isServer())
	//		network->sendThrowDice(1, 2, 3, 4, 5, 6);

	//	b = true;
	//	while (b)
	//	{
	//		remoteInput	inp = network->getRemoteInput();
	//		if (inp.action != NO_TYPE)
	//		{
	//			b = false;
	//			//cout << "Received a " << inp.action << endl;
	//		}
	//		if (network->error())
	//		{
	//			cout << "ERROR: " << network->errMessage() << endl;
	//			b = false;
	//		}
	//	}

	//	if (network->isServer())
	//		network->sendSafeOpened(TIARA);

	//    b = true;
	//	while (b)
	//	{
	//		remoteInput	inp = network->getRemoteInput();
	//		if (inp.action != NO_TYPE)
	//		{
	//			b = false;
	//			//cout << "Received a " << inp.action << endl;
	//		}

	//		if (network->error())
	//		{
	//			cout << "ERROR: " << network->errMessage() << endl;
	//			b = false;
	//		}
	//	}


	//

	//}
	//getchar();
	//getchar();
	
	return 0;
}