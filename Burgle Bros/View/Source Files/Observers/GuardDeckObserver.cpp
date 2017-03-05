#include "../../Header Files/Observers/GuardDeckObserver.h"
#include "../../Header Files/MoveAnimation.h"

GuardDeckObserver::GuardDeckObserver(Floor* f, Container* p)
{
	deck = f->getPatrolDeck();
	floor = f;
	parent = p;
	startedRetraction = false;
	deckView = new Container(p->getHeight()/5, p->getWidth());
	deckView->setPosition(p->getHeight() *4.0/ 5, 0);
	deckView->setName(string("Deck from floor ") + to_string(floor->number()));
	zoom = new Container(p->getWidth(),p->getWidth() );
	zoom->setPosition(0, 0);
	p->addObject(deckView);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			string des = string("A") + to_string(j + 1) + string(".png");
			des[0] += i;
			cards[i][j] = new Image(string("../View/Images/Patrol/PC ") +des);
			cards[i][j]->setScale(0.9*double(zoom->getHeight()) / 4.0 / cards[i][j]->getHeight());
			cards[i][j]->setPosition(double(zoom->getHeight()) / 4.0*j, double(zoom->getHeight()) / 4.0*i);
		}
	}
	deckO = new GuardCardObserver(deckView, deck->getDeck().back());
	graveO = new GuardCardObserver(deckView, deck->getDiscarded().back());
	deckO->setPos(0, 0);
	graveO->setPos(0, deckView->getWidth()/4 );
	deck->attach(this);
}

void GuardDeckObserver::update()
{
	if (deck->getDiscarded().empty()==true)
	{
		graveO->setOn(false);
	}
	else
	{
		graveO->setCard(deck->getDiscarded().back());
		graveO->setOn(true);
		
	}
	if (deck->getDeck().empty() == true)
	{
		deckO->setOn(false);
	}
	else
	{
		deckO->setCard(deck->getDeck().back());
		deckO->setOn(true);
		
	}

	
	// If the discarded deck is clicked and the animation is not running, start animation
	if (graveO->isClicked() == true && parent->contains(zoom) == false)
	{
		zoom->clear();
		pair<int, int> discardedPos(parent->getHeight() *4.0 / 5, parent->getWidth() / 4.0);
		for (auto& card : deck->getDiscarded())
		{
			int i = card->getDescription()[0] - 'A';
			int j = card->getDescription()[1] - '1';
			cards[i][j]->deleteAnimation();
			pair<int, int> cardPos(j*double(parent->getWidth()) / 4.0, i*double(parent->getWidth()) / 4.0);
			cards[i][j]->setPosition(zoom->getHeight(), double(zoom->getWidth()) / 4.0);
			cards[i][j]->addAnimation(new MoveAnimation(discardedPos, cardPos, 0.3));
			zoom->addObject(cards[i][j]);
		}
		startedRetraction = false;
		parent->addObject(zoom);
	}
	// If the discarded deck is not clicked and the animation is running, stop the animation
	else if(graveO->isClicked()==false && parent->contains(zoom) == true)
	{
		pair<int, int> discardedPos(parent->getHeight() *4.0 / 5, parent->getWidth() / 4.0);
		for (auto& card : deck->getDiscarded())
		{
			int i = card->getDescription()[0] - 'A';
			int j = card->getDescription()[1] - '1';
			if (startedRetraction == false)
			{
				cards[i][j]->deleteAnimation();
			}
			
			if (cards[i][j]->hasAnimation() == false && startedRetraction==false)
			{
				cards[i][j]->addAnimation(new MoveAnimation(cards[i][j]->getPos(), discardedPos, 0.3));
			}
			else if (cards[i][j]->animationFinished() == true)
			{
				startedRetraction = false;
				cards[i][j]->deleteAnimation();
				parent->removeObject(zoom);
				zoom->clear();
			}
		}
		startedRetraction = true;
		
	}
	
	deckO->update();
	graveO->update();
}