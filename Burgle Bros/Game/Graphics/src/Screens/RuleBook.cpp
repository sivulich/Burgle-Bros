#include "RuleBook.h"

RuleBook::RuleBook() : Container(SCREEN_HEIGHT, SCREEN_WIDTH, "RULE_BOOK")
{
	currentPage = 0;
	setPosition(SCREEN_HEIGHT*0.5 - h / 2, SCREEN_WIDTH*0.5 - w / 2);
	//setBorderVisible(true);
	left = new Image(string("./Graphics/Images/RuleBook/LEFT_ARROW.png"));
	left->setScale(0.3);
	//left->setBorderVisible(true);
	left->setPosition(h*0.5 - left->getHeight()*left->getScale()*0.5, 0);
	right = new Image(string("./Graphics/Images/RuleBook/RIGHT_ARROW.png"));
	right->setScale(0.3);
	right->setPosition(h*0.5 - right->getHeight()*right->getScale()*0.5, w-right->getWidth()*right->getScale());
	//right->setBorderVisible(true);
	
	for (unsigned i = 0; i < totalPages; i++)
	{
		pages.push_back(new Image("./Graphics/Images/RuleBook/" + to_string(i+1) + ".png"));
		if (pages[i]->getWidth()*h > pages[i]->getHeight()*w)
		{
			pages[i]->setScale(w*1.0 / pages[i]->getWidth());
		}
		else
		{
			pages[i]->setScale(h*1.0 / pages[i]->getHeight());
		}
		pages[i]->setPosition(h / 2 - pages[i]->getHeight()*pages[i]->getScale()*0.5, w / 2 - pages[i]->getWidth()*pages[i]->getScale()*0.5);
		pages[i]->setVisible(false);
		pages[i]->setHoverable(false);
		pages[i]->setClickable(false);
		addObject(pages[i]);
	}
	pages[0]->setVisible(true);
	left->setVisible(false);
	addObject(left);
	addObject(right);

}
string
RuleBook::click(int y, int x)
{
	string s = Container::click(y, x);
	if (s == "LEFT_ARROW")
	{
		if (currentPage > 0)
			currentPage--;
		changePage();
	}
	else if (s == "RIGHT_ARROW")
	{
		if (currentPage < pages.size()-1 )
			currentPage++;
		changePage();
	}
	
	return s;
}
bool
RuleBook::overYou(int y, int x)
{
	left->setVisible(false);
	right->setVisible(false);
	if (currentPage>0 && left->isInside((y - this->y)*1.0 / scaleY, (x - this->x)*1.0 / scaleX))
		left->setVisible(true);
	else
		left->setVisible(false);

	if (currentPage<pages.size() - 1 && right->isInside((y - this->y)*1.0 / scaleY, (x - this->x)*1.0 / scaleX))
		right->setVisible(true);
	else
		right->setVisible(false);
	return Container::overYou(y, x);
}

void
RuleBook::changePage()
{
	for (auto& p : pages)
		p->setVisible(false);
	pages[currentPage]->setVisible(true);
}

RuleBook::~RuleBook()
{
}
