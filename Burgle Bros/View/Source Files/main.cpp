
#include "../../Model/Header Files/GameModel.h"
#include "../Header Files/Allegro.h"
#include "../Header Files/object.h"
#include "../Header Files/Observers/GameObserver.h"

bool isCoord(string& s)
{

	if (s[0]<'A' || s[0]>'D')
		return false;
	if (s[1]<'1' || s[1]>'4')
		return false;
	if (s[2] != 'F')
		return false;
	if (s[3] < '0' || s[3]>'2')
		return false;
	return true;
}
int main(void)
{
	Allegro al;
	al_rest(0.1);
	if (al.wasInitOk() == true)
	{
		
		GameModel game;
		game.setBoard();
		game.getPlayer1()->setPosition(game.getBoard()[0][0][0]);
		game.getPlayer1()->setCharacter(HACKER);
		game.getPlayer1()->setActionTokens(100000);
		game.getPlayer2()->setPosition(game.getBoard()[1][0][0]);
		game.getPlayer2()->setCharacter(RAVEN);
		game.getPlayer2()->setActionTokens(100000);
		GameObserver view(&game, int(720));
		
		string in;
		Timer time(1.0 / 30.0);
		time.start();
		long long c=time.getCount();
		while (in != "exit")
		{
			in = view.input();
			if (in != "")
			{
				cout << "Input " << in << endl;

				if (isCoord(in))
				{
					//board[in[3] - '0'][in[0] - 'A'][in[1] - '1']->flip();
					game.getPlayer1()->move(Coord(in[3] - '0', in[0] - 'A', in[1] - '1'));
					game.getBoard()[in[3] - '0'].moveGuard();
				}
				else if (in.substr(0, 5) == "PC RF")
				{
					game.getBoard()[in[5] - '0'].getPatrolDeck()->discardTop();
				}
					
				
			}
			if (c < time.getCount()&& view.isEmpty()==true )
			{
				c = time.getCount();
				view.update();
			}
		}
			
	}
		
	return 0;
}