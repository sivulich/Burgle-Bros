#pragma once
#include "./Configs.h"


// HACE FALTA ESTO?? PARA ESTO NO ESTA EL PROTOCOLO?


class actionNode
{
public:
	/**
		Creates an action node
	*/
	actionNode(string action, Coord c, int t) : myAction(action), coord(c), turn(t) {};

	/**
		Sets true to know the action was sent.
	*/
	void setSentOk() { sent = true; };

	/**
		Returns true if the action was already sent.
	*/
	bool isSent() { return sent; };

	// Coord where the action occured 
	Coord coord;

	// String with action enum
	string myAction;

	// Number of turn in which action occured
	int turn;

private:
	bool sent;
};