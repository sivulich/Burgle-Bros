#pragma once
#include "Container.h"
#include "../../include/GraphicsDefs.h"
#include "Image.h"

class RuleBook :
	public Container
{
public:
	RuleBook();
	string click(int y, int x)override;
	bool overYou(int y, int x)override;
	~RuleBook();
private:
	unsigned int totalPages = 6;
	void changePage();
	vector<Image*> pages;
	Image* left, *right;
	unsigned currentPage;
};

