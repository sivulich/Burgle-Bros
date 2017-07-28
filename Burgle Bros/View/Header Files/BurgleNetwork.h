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
#define MAX_CONNECTION_WAIT 20
#define MAX_PACKET_WAIT 2

typedef struct {
	atomic_bool error;
	atomic_int currState;
	atomic_bool usingData;
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


using namespace std;
enum{WAITINNG_CONN=1,MACHINES_CONNECTED,EXCHANGE_NAMES,EXCHANGE_CHARACTERS,EXCHANGE_GUARD,EXCHANGE_BOARD,EXCHANGE_FINISHED};
#define PORT 15251


class BurgleNetwork
{
public:
	BurgleNetwork(const string IP);
	bool error() { return flags.error; };
	bool join();
	bool startupPhase(const string& name, const characterType type, const Coord guardPos, const Coord guardTarget, Board& board, const Coord playerPos);
	string errMessage() { return flags.errMessage; };
	bool server() { return flags.server; };
	~BurgleNetwork();
private:
	void establishConn(thData* fl, string IP);
	void exchangeNames(thData* fl,const string& name);
	void exchangeCharacters(thData* fl, const characterType type);
	void exchangeGuard(thData* fl, const Coord guardPos, Coord guardTarget);
	void exchangeBoard(thData* fl, Board& board, const Coord playerPos);
	bool sendPacket(apr_socket_t* sock, const vector<char>& dat);
	thData flags;
	thread* currThread;
};

