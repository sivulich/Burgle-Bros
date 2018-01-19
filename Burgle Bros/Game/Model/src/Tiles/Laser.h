#pragma once
#include "Tile.h"
#include "../PlayerInterface.h"
#include "ComputerRoomL.h"
/*
It takes two actions to enter this tile. If you can't or you don't want to spend the extra action, an Alarm 
goes off unless you us a Hack token from the Laser Computer Room
*/

// SI EL PLAYER QUIERE ENTRAR A LA TILE, EL MODELO LE PREGUNTA AL USUARIO SI QUIERE USAR UN HACK TOKEN O GASTAR DOS ACCIONES PARA APAGAR LA ALARMA
// SI LO QUIERE GASTAR, DESPUES DE MOVER AL PLAYER LLAMA A doaction CON "SPENT_OK" 

class Laser :
	public Tile
{
public:
	Laser(int floor, int col, int row) : Tile(LASER, floor, col, row) {};
	~Laser();

	/**
	Executes the tile's special actions, if any...
	@param p player who is moving
	*/
	virtual void enter(PlayerInterface * player) override;

	/**
	Returns a vector of strings with the actions the player can do on the tile they are on
	@param p Player who wants to check the actions
	*/
	virtual vector<string> getActions(PlayerInterface * player) override;

	/**
	Applies the action given to the player
	@param action Action to execute
	@param p Player who wants to do the action
	*/
	virtual bool doAction(string action, PlayerInterface * player) override;

	virtual void exit(PlayerInterface * player) override;

	void setComputerRoom(ComputerRoomL * c) { computerRoom = c; };

	bool isHackerHere() { return hackerHere; };

private:
	ComputerRoomL * computerRoom;
};

