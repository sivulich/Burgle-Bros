#include "../Screen.h"
#include "../Container.h"
#include "../Model/Header Files/GameModel.h"
#include "Observer.h"
#include "BoardObserver.h"
#include "LocalPlayerObserver.h"
#include "../Controller/Header Files/localControler.h"
class GameObserver :public Observer {
public:
	GameObserver(GameModel* g,int sHeight);
	void update();
	bool empty() { return in->empty(); };
	string input();
	~GameObserver();
private:
	Screen* screen;
	GameModel* game;
	Container* cont;
	localControler* in;
	BoardObserver* board;
	LocalPlayerObserver * pl;
};

