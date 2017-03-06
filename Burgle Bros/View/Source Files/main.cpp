

#include "../Header Files/Screen.h"
#include "../Header Files/Image.h"
#include "../Header Files/Container.h"
#include "../Header Files/Button.h"
#include "../../Controller/Header Files/localControler.h"
#include "../Header Files/Textbox.h"
#include "../../Model/Header Files/Board.h"
#include "../Header Files/Allegro.h"
#include "../Header Files/Observers/BoardObserver.h"
#include "../Header Files/object.h"
#include "../Header Files/Observers/LocalPlayerObserver.h"

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
		Screen screen(1000,1000* 1280.0/720.0, string("../View/Images/BackGround.jpg"),false);
		screen.backgroundProperties(0, 0, 1000.0 / 1080.0);
		Container cont(1000, 1000 * 1280.0 / 720.0);
		Board board;
		
		localControler control(&screen);
		
		for (int i = 0; i < 3; i++)
		{
			board[i].setNumber(i);
			board[i].getPatrolDeck()->createDeck(i);
		}
		
		board.setBoard();
		board.setWalls();
		board.parseBoard();
		Player player(&board);
		BoardObserver obs(&board, &cont);
		player.setPosition(board[0][0][0]);
		player.setCharacter(JUICER);
		player.setActionTokens(100000);
		LocalPlayerObserver pobs(&player, &obs, &cont);
		
		board[0][0][0]->flip();
		player.setPosition(board[0][0][0]);
		screen.addObject(&cont);
		string in;
		Timer time(1.0 / 30.0);
		time.start();
		long long c=time.getCount();
		while (in != "exit")
		{
			in = control.input();
			if (in != "")
			{
				cout << "Input " << in << endl;

				if (isCoord(in))
				{
					board[in[3] - '0'][in[0] - 'A'][in[1] - '1']->flip();
					player.move(Coord(in[3] - '0', in[0] - 'A', in[1] - '1'));
				}
				else if (in.substr(0, 5) == "PC RF")
				{
					board[in[5] - '0'].getPatrolDeck()->discardTop();
				}
					
				
			}
			if (c < time.getCount()&& control.empty()==true )
			{
				c = time.getCount();
				obs.update();
				screen.draw();
			}
		}
			
	}
		
	return 0;
}