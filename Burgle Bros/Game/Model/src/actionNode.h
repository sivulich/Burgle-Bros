#pragma once
#include "./Configs.h"


// HACE FALTA ESTO?? PARA ESTO NO ESTA EL PROTOCOLO?


class actionNode
{
public:
	/**
		Creates an action node
	*/
	actionNode(string action, Coord c, int t, int d) : myAction(action), coord(c), turn(t), dice(d) {};

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

	// Dice thrown during action if any was thrown
	int dice;

private:
	bool sent;
};