#pragma once
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <time.h>
#include <chrono>
#define APR_DECLARE_STATIC 
#include <apr_general.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include <apr_network_io.h>
#include "../../Model/Header Files/Board.h"
#include "../../Model/Header Files/Characters/Character.h"
#define DEF_SOCK_TIMEOUT (APR_USEC_PER_SEC * 5) 
#define MAX_CONNECTION_WAIT 120
#define MAX_PACKET_WAIT 60

typedef struct {
	atomic_bool error;
	atomic_int currState;
	atomic_bool usingData;
	atomic_bool iStart;
	atomic_bool join;
	atomic_bool executing;
	atomic_bool exit;
	string errMessage;
	atomic_bool server;
	apr_socket_t* sock;
	apr_pool_t* pool;
	string remoteName;
	characterType remotePlayer;
	vector<tileType> remoteBoard;
	Coord remoteGuardPos, remoteGuardTarget,playerPos;
}thData;

class remoteInput{
public:
	action_ID action;
	char dice[6];
	Coord pos;
	vector<Coord> guardMoves;
	lootType loot;
	char modifier;
};
using namespace std;
enum{WAITINNG_CONN=1,MACHINES_CONNECTED,EXCHANGE_NAMES,EXCHANGE_CHARACTERS,EXCHANGE_GUARD,EXCHANGE_BOARD,EXCHANGE_FIRST,EXCHANGE_FINISHED};
#define PORT 15251
#define NO_PACKET vector<char>()

class BurgleNetwork
{
public:
	BurgleNetwork(const string IP);
	/*It should always be checked before calling any method on this class*/
	bool error() { return flags.error; };
	//Returns the error message generated, to print in any display
	string errMessage() { return flags.errMessage; };

	/*It tells you if the last communication finished, never continue excecuting without checking the return value as true*/
	bool join();

	/*Exchanges information with Client/Server about the game*/
	bool startupPhase(const string& name, const characterType type, const Coord guardPos, const Coord guardTarget, Board& board, const Coord playerPos);

	/*Information getters*/
	characterType remotePlayer() { return flags.remotePlayer; };
	vector<tileType> remoteBoard(){ return flags.remoteBoard; };
	Coord remoteGuardPos() { return flags.remoteGuardPos; };
	Coord remoteGuardTarget() { return flags.remoteGuardTarget; };
	Coord startingPos() { return flags.playerPos; };
	string remoteName() { return flags.remoteName; };
	bool server() { return flags.server; };
	remoteInput getRemoteInput();

	/*Instruction senders*/
	void sendPeek(Coord pos, char num);
	void sendMove(Coord pos, char num);
	void sendSpent(char yn);
	void sendAddToken(Coord pos);
	void sendUseToken(Coord pos);
	void sendThrowDice(char d1, char d2, char d3, char d4, char d5, char d6);
	void sendSafeOpened(lootType loot);
	void sendCreateAlarm(Coord pos);
	void sendSpyPatrol(Coord pos, char tb);
	void sendPlaceCrow(Coord pos);
	void sendOfferLoot(lootType loot);
	void sendRequestLoot(lootType loot);
	void sendInitialGuardPos(Coord pos);
	void sendPickupLoot();
	void sendPass();
	void sendAgree();
	void sendDisagree();
	void sendQuit();
	void sendError();
	void sendGuardMovement(vector<Coord>& path);
	void sendLootDice(char dice);

	~BurgleNetwork();
private:
	/*Startup*/
	void establishConn(thData* fl, string IP);
	void exchangeNames(thData* fl,const string& name);
	void exchangeCharacters(thData* fl, const characterType type);
	void exchangeGuard(thData* fl, const Coord guardPos, Coord guardTarget);
	void exchangeBoard(thData* fl, Board& board, const Coord playerPos);
	void exchangeFirst(thData* fl);

	/*Utility*/
	void instructionWithMod(thData* fl, action_ID act, char modifier);
	void packetAndAck(thData* fl, vector<char>& pack);
	void packetAndAckThreded(thData* fl, vector<char> pack);
	void instructionWithCoord(thData* fl, action_ID act, Coord pos, char modifier);
	bool recievePacket(apr_socket_t* sock, vector<char>& dat);
	bool sendPacket(apr_socket_t* sock, const vector<char>& dat);
	void threadStarter(thData* fl);
	void threadCloser(thData* fl);
	void coordToPacket(Coord pos, vector<char>& pack);
	void packetToInput(remoteInput& inp, vector<char>& pack);
	bool answerInput(remoteInput& inp);
	thData flags;
	thread* currThread;
};
