#pragma once
#include "Configs.h"
class actionNode
{
public:
	string myAction;

	actionNode(string & action);
	/**
		Sets true to know the action was sent.
	*/
	void setSentOk() { sent = true; };

	/**
		Returns true if the action was already sent.
	*/
	bool isSent() { return sent; };
private:
	bool sent;
};

