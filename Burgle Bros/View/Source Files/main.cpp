

#include "../Header Files/Screen.h"
#include "../Header Files/Image.h"
#include "../Header Files/Container.h"
#include "../Header Files/Button.h"
#include "../../Controller/Header Files/localControler.h"
#include "../Header Files/Textbox.h"
#include "../../Model/Header Files/Board.h"
#include "../Header Files/Allegro.h"
#include "../Header Files/BoardObserver.h"
#include "../Header Files/object.h"
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
		Screen screen(720,720* 1280.0/720.0, string("../View/Images/BackGround.jpg"),false);
		Container cont(720, 720 * 1280.0 / 720.0);
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
		BoardObserver obs(&board, &cont);
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
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 4; j++)
						for (int k = 0; k < 4; k++)
							obs[i][j][k]->setHoverable(false);
				if (in.substr(0,4) == "PC R")
					board[in[5]-'0'].getPatrolDeck()->discardTop();
				else
					for (int i = 0; i < 3; i++)
						if (board[i].getPatrolDeck()->isEmpty() == true)
							board[i].getPatrolDeck()->reset(6);
				if (isCoord(in))
				{
					if (board[in[3] - '0'][in[0] - 'A'][in[1] - '1']->isFlipped() == false)
						board[in[3] - '0'][in[0] - 'A'][in[1] - '1']->turnUp();
						vector<Coord> adjacent = board[in[3] - '0'][in[0] - 'A'][in[1] - '1']->whereCanIPeek();
						for (auto& c : adjacent)
						{
							obs[c.floor][c.col][c.row]->setHoverable(true);
						}
				}
				
			}
			if (c < time.getCount())
			{
				c = time.getCount();
				obs.update();
				screen.draw();
			}
		}
			
	}
		
	return 0;
}