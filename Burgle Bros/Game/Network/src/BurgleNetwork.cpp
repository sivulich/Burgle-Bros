#include "./BurgleNetwork.h"
#include <chrono>


ALLEGRO_EVENT_SOURCE BurgleNetwork::networkEventSource;
ALLEGRO_EVENT BurgleNetwork::connectedEvent;

action_ID char2action_ID(char c)
{
	switch ((unsigned char)c)
	{
	case 0x00:
		return NO_TYPE;
	case 0x01:
		return ACK;
	case  0x02:
		return AGREE;
	case 0x03:
		return DISAGREE;
	case 0x10:
		return NAME;
	case 0x11:
		return NAME_IS;
	case 0x12:
		return I_AM;
	case 0x13:
		return INITIAL_G_POS;
	case  0x14:
		return START_INFO;
	case  0x20:
		return YOU_START;
	case 0x21:
		return I_START;
	case 0x30:
		return PEEK;
	case  0x31:
		return MOVE;
	case  0x32:
		return SPENT_OK;
	case 0x33:
		return ADD_TOKEN;
	case 0x34:
		return USE_TOKEN;
	case  0x35:
		return THROW_DICE;
	case 0x36:
		return SAFE_OPENED;
	case 0x37:
		return CREATE_ALARM;
	case 0x38:
		return SPY_PATROL;
	case 0x39:
		return PLACE_CROW;
	case 0x3A:
		return OFFER_LOOT;
	case 0x3B:
		return REQUEST_LOOT;
	case 0x3C:
		return PICK_UP_LOOT;
	case 0x3D:
		return PASS;
	case 0x3E:
		return ROLL_DICE_FOR_LOOT;
	case 0x3F:
		return GUARD_MOVEMENT;
	case  0x40:
		return WE_WON;
	case  0x41:
		return WE_LOST;
	case 0x42:
		return GAME_OVER;
	case 0xFE:
		return QUIT;
	case 0xFF:
		return ERRO;
	default:
		return NO_TYPE;
	}
}
ALLEGRO_EVENT BurgleNetwork::getEvent()
{
	ALLEGRO_EVENT e = eventQueue.front();
	eventQueue.pop();
	return e;
}

BurgleNetwork::BurgleNetwork()
{
	connectedEvent.user.type = NETWORK_CONNECTED;
}

void BurgleNetwork::connect(string IP)
{
	flags.currState = WAITINNG_CONN;
	flags.exit = false;
	flags.error = false;
	flags.connected = false;
	apr_initialize();
	currThread = new thread(&BurgleNetwork::establishConn, this, &flags, IP);
}

void BurgleNetwork::cancelConnecting()
{
	if (flags.currState == WAITINNG_CONN)
		currThread->~thread();
}

bool BurgleNetwork::join()
{
	this_thread::sleep_for(chrono::milliseconds(10));
	if (flags.join == true)
	{
		currThread->join();
		currThread = nullptr;
		flags.join = false;
		return true;
	}
	else
	{
		if (flags.executing == true)
			return false;
		else
			return true;

	}
}
void BurgleNetwork::threadStarter(thData* fl)
{
	//Probando
	//fl->join = false;
	fl->executing = true;
}

void BurgleNetwork::threadCloser(thData* fl)
{
	fl->executing = false;
	fl->join = true;
}

bool BurgleNetwork::sendPacket(apr_socket_t* sock, const vector<char>& dat)
{
	apr_size_t size = dat.size();
	apr_status_t rv;
	if (dat.size() == 0)
		return true;
	rv = apr_socket_send(sock, dat.data(), &size);
	if (rv == APR_SUCCESS)
		return true;
	cout << "Couldnt send packet" << endl;
	return false;
}

bool BurgleNetwork::recievePacket(apr_socket_t* sock, vector<char>& dat)
{
	vector<char> buffer(1024, 0);
	apr_size_t size = 1024;
	clock_t t = clock();
	apr_status_t rv;
	do {
		if (size == 0)
			size = 1024;
		rv = apr_socket_recv(sock, buffer.data(), &size);
	} while (double(clock() - t) / CLOCKS_PER_SEC < MAX_PACKET_WAIT && (APR_STATUS_IS_EOF(rv) || size == 0));

	if (size == 1024 || size == 0)
		return false;
	dat.insert(dat.end(), buffer.begin(), buffer.begin() + size);
	return true;
}

void BurgleNetwork::exchangeNames(thData* fl, const string& name)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);
	//First contact server sends NAME, client listens
	if (fl->server == true)
	{
		vector<char> pack(1);
		pack[0] = NAME;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send first packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	else
	{
		vector<char> buffer;
		bool b;
		clock_t t = clock();
		do {
			b = recievePacket(fl->sock, buffer);
		} while (double(clock() - t) / CLOCKS_PER_SEC < MAX_CONNECTION_WAIT && b == false);
		if (b== false || buffer.size() != 1 || buffer[0] != NAME)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve first packet";
			return;
		}

	}
	this_thread::sleep_for(chrono::milliseconds(10));
	//Second packet Client sends NAME_IS, server listens
	if (fl->server == true)
	{
		vector<char> buffer;
		bool b;
		clock_t t = clock();
		do {
			b = recievePacket(fl->sock, buffer);
		} while (double(clock() - t) / CLOCKS_PER_SEC < MAX_CONNECTION_WAIT && b==false);
		if (b == false || buffer.size() == 0 || buffer[0] != NAME_IS)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve second packet";
			return;
		}
		int n = buffer[1];
		for (int i = 2; i < 2 + n; i++)
			fl->remoteName.push_back(buffer[i]);
	}
	else
	{
		vector<char> pack(2 + name.size());
		pack[0] = NAME_IS;
		pack[1] = (char)name.size();
		for (unsigned int i = 2; i < pack.size(); i++)
		{
			pack[i] = name[i - 2];
		}
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send second packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	this_thread::sleep_for(chrono::milliseconds(10));
	//Third packet Server sends ACK, client listens
	if (fl->server == true)
	{
		vector<char> pack(1);
		pack[0] = ACK;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send third packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	else
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != ACK)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve third packet";
			return;
		}

	}
	this_thread::sleep_for(chrono::milliseconds(10));
	//Fourth packet client sends NAME, server listens
	if (fl->server == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != NAME)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve fourth packet";
			return;
		}
	}
	else
	{
		vector<char> pack(1);
		pack[0] = NAME;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send fourth packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));

	}
	this_thread::sleep_for(chrono::milliseconds(10));
	//Fifth packet server sends NAME_IS, client listens
	if (fl->server == true)
	{
		vector<char> pack(2 + name.size());
		pack[0] = NAME_IS;
		pack[1] = (char)name.size();
		for (unsigned int i = 2; i < pack.size(); i++)
		{
			pack[i] = name[i - 2];
		}
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send fifth packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	else
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() == 0 || buffer[0] != NAME_IS)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve fifth packet";
			return;
		}
		int n = buffer[1];
		for (int i = 2; i < 2 + n; i++)
			fl->remoteName.push_back(buffer[i]);
	}
	this_thread::sleep_for(chrono::milliseconds(10));
	//Sixth packet client sends ACK,server listens
	if (fl->server == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != ACK)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve sixth packet";
			return;
		}
	}
	else
	{
		vector<char> pack(1);
		pack[0] = ACK;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send sixth packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	threadCloser(fl);
	return;
}

void BurgleNetwork::exchangeCharacters(thData* fl, const characterType type)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	//First packet server sends I_AM, client listens
	if (fl->server == true)
	{
		vector<char> pack(2);
		pack[0] = I_AM;
		pack[1] = (char)type;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send first packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	else
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 2 || buffer[0] != I_AM)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve first packet";
			return;
		}
		fl->remotePlayer = (characterType)buffer[1];
	}
	this_thread::sleep_for(chrono::milliseconds(10));

	//Second packet server listens, client sends I_AM
	if (fl->server == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 2 || buffer[0] != I_AM)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve second packet";
			return;
		}
		fl->remotePlayer = (characterType)buffer[1];
	}
	else
	{
		vector<char> pack(2);
		pack[0] = I_AM;
		pack[1] = (char)type;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send second packet";
			return;
		}

	}

	threadCloser(fl);
	return;
}

void BurgleNetwork::exchangeGuard(thData* fl, const Coord guardPos, Coord guardTarget)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	//First packet server sends INITIAL_G_POS, client listens
	if (fl->server == true)
	{
		vector<char> pack(9);
		pack[0] = INITIAL_G_POS;
		pack[1] = guardPos.col + 'A';
		pack[2] = guardPos.row + '1';
		pack[3] = 'F';
		pack[4] = guardPos.floor + '1';
		pack[5] = guardTarget.col + 'A';
		pack[6] = guardTarget.row + '1';
		pack[7] = 'F';
		pack[8] = guardTarget.floor + '1';
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send first packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	else
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 9 || buffer[0] != INITIAL_G_POS)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve first packet";
			return;
		}
		fl->remoteGuardPos.col = buffer[1] - 'A';
		fl->remoteGuardPos.row = buffer[2] - '1';
		fl->remoteGuardPos.floor = buffer[4] - '1';
		fl->remoteGuardTarget.col = buffer[5] - 'A';
		fl->remoteGuardTarget.row = buffer[6] - '1';
		fl->remoteGuardTarget.floor = buffer[8] - '1';
	}
	this_thread::sleep_for(chrono::milliseconds(10));

	//Second packet server listens, client sends ACK
	if (fl->server == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != ACK)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve second packet";
			return;
		}
	}
	else
	{
		vector<char> pack(1);
		pack[0] = ACK;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send second packet";
			return;
		}

	}

	threadCloser(fl);
	return;
}
void BurgleNetwork::exchangeBoard(thData* fl,/* Board& board*/ vector<tileType> board, const Coord playerPos/*,int initialSafeNumber*/)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	//First packet server sends INITIAL_G_POS, client listens
	if (fl->server == true)
	{
		vector<char> pack(1);
		pack[0] = START_INFO;
		for(size_t i=0; i<48; i++)
			pack.push_back((char)board[i]);
	/*	for (size_t f = 0; f < 3; f++)
		{
			for (size_t r = 0; r < 4; r++)
			{
				for (size_t c = 0; c < 4; c++)
				{
					pack.push_back((char)(board[f][r][c]->getType()));
				}
			}
		}*/
		pack.push_back((char)(playerPos.col + 'A'));
		pack.push_back((char)(playerPos.row + '1'));
		pack.push_back('F');
		pack.push_back((char)(playerPos.floor + '1'));
		//pack.push_back((char)(initialSafeNumber+'0'));
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send first packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	else
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 53 /*54!*/|| buffer[0] != START_INFO)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve first packet";
			return;
		}
		for (int i = 1; i < 49; i++)
		{
			fl->remoteBoard.push_back((tileType)buffer[i]);
		}
		fl->playerPos.col = buffer[49] - 'A';
		fl->playerPos.row = buffer[50] - '1';
		fl->playerPos.floor = buffer[52] - '1';
		//fl->initialSafeNumber = buffer[52] - '0';
	}

	//Second packet server listens, client sends ACK
	if (fl->server == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != ACK)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve second packet";
			return;
		}
	}
	else
	{
		vector<char> pack(1);
		pack[0] = ACK;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send second packet";
			return;
		}

	}

	threadCloser(fl);
	return;
}
void BurgleNetwork::exchangeFirst(thData* fl)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	//First packet server sends I_START/YOU_START , client listens
	if (fl->server == true)
	{
		vector<char> pack(1);
		fl->iStart = (bool)(rand() % 2);
		pack[0] = (fl->iStart == true ? I_START : YOU_START);
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send first packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	else
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || (buffer[0] != I_START && buffer[0] != YOU_START))
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve first packet";
			return;
		}
		fl->iStart = (buffer[0] == YOU_START ? true : false);
	}
	this_thread::sleep_for(chrono::milliseconds(10));
	//If server starts, client sends ACK, server listens
	if (fl->server == true && fl->iStart == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != ACK)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve second packet";
			return;
		}
	}
	else if (fl->server == false && fl->iStart == false)
	{
		vector<char> pack(1);
		pack[0] = ACK;
		if (sendPacket(fl->sock, pack) == false)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Couldnt send second packet";
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	threadCloser(fl);
	return;
}
bool BurgleNetwork::startupPhase(const string& name, const characterType type, const Coord guardPos, const Coord guardTarget, /* Board& board*/ vector<tileType> board, const Coord playerPos)
{
	if (flags.error == true)
		return false;
	if (flags.currState == MACHINES_CONNECTED)
	{
		flags.currState = EXCHANGE_NAMES;
		currThread = new thread(&BurgleNetwork::exchangeNames, this, &flags, name);
	}
	else if (flags.currState == EXCHANGE_NAMES)
	{
		if (!join())
			return false;
		if (flags.remoteName == name)
		{
			flags.error = true;
			flags.errMessage = "Duplicate names";
			return false;
		}
		cout << "Name exchange succesfull I am " << name << ". Remote Name: " << flags.remoteName << endl;
		flags.currState = EXCHANGE_CHARACTERS;
		currThread = new thread(&BurgleNetwork::exchangeCharacters, this, &flags, type);
	}
	else if (flags.currState == EXCHANGE_CHARACTERS)
	{
		if (!join())
			return false;
		if (type == flags.remotePlayer)
		{
			flags.error = true;
			flags.errMessage = "Duplicate characters selected";
			return false;
		}
		cout << "Character exchange succesfull I am " << toString(type) << ". Remote Character is: " << toString(flags.remotePlayer) << endl;
		flags.currState = EXCHANGE_GUARD;
		currThread = new thread(&BurgleNetwork::exchangeGuard, this, &flags, guardPos, guardTarget);
	}
	else if (flags.currState == EXCHANGE_GUARD)
	{
		if (!join())
			return false;
		cout << "Guard exchange succesfull" << endl;
		flags.currState = EXCHANGE_BOARD;
		currThread = new thread(&BurgleNetwork::exchangeBoard, this, &flags, board, playerPos);
	}
	else if (flags.currState == EXCHANGE_BOARD)
	{
		if (!join())
			return false;
		cout << "Board exchange succesfull" << endl;
		flags.currState = EXCHANGE_FIRST;
		currThread = new thread(&BurgleNetwork::exchangeFirst, this, &flags);
	}
	else if (flags.currState == EXCHANGE_FIRST)
	{
		if (!join())
			return false;
		cout << "First is " << (flags.iStart ? "Me" : "Remote") << endl;
		flags.currState = EXCHANGE_FINISHED;
		return true;
	}
	else
	{
		flags.error = true;
		flags.errMessage = "Invalid state for startup phase";
		return false;
	}
	return false;
}

void BurgleNetwork::establishConn(thData* fl, string IP)
{
	if (fl->error == true)
		return;
	fl->error = false;
	fl->executing = true;
	fl->join = false;
	apr_status_t rv;
	apr_sockaddr_t * connectionSock;
	rv = apr_pool_create(&(fl->pool), NULL);
	if (rv == APR_SUCCESS)
	{
		rv = apr_sockaddr_info_get(&connectionSock, IP.c_str(), APR_INET, PORT, 0, fl->pool);//cambiar UNSPEC por APR_INET
		if (rv == APR_SUCCESS)
		{
			rv = apr_socket_create(&fl->sock, APR_INET, SOCK_STREAM, APR_PROTO_TCP, fl->pool);
			if (rv == APR_SUCCESS)
			{
				apr_socket_opt_set(fl->sock, APR_SO_NONBLOCK, 1);
				apr_socket_timeout_set(fl->sock, DEF_SOCK_TIMEOUT);

				using namespace chrono;
				DEBUG_MSG("Trying to connect as client\n");
				high_resolution_clock::time_point curr, start;
				start = high_resolution_clock::now();
				double timeToWait = (200.0 + double(rand() % 9800));
				bool end = false;
				while (duration_cast<milliseconds>(high_resolution_clock::now() - start).count() < timeToWait)
				{
					rv = apr_socket_connect(fl->sock, connectionSock);
					if (rv == APR_SUCCESS)
						break;
				}

				if (rv == APR_SUCCESS)
				{
					apr_socket_opt_set(fl->sock, APR_SO_NONBLOCK, 1);
					apr_socket_timeout_set(fl->sock, 0);
					fl->connected = true;
					fl->server = false;
					fl->executing = false;
					fl->join = true;
					fl->error = false;
					fl->currState = MACHINES_CONNECTED;
					//al_emit_user_event(&networkEventSource, &connectedEvent, NULL);
					eventQueue.push(connectedEvent);
					DEBUG_MSG("Connected as client!");
				}
				else
				{
					apr_socket_t* temp;
					fl->sock = nullptr;
					rv = apr_sockaddr_info_get(&connectionSock, nullptr, APR_INET, PORT, 0, fl->pool);
					if (rv != APR_SUCCESS)
						cout << "ERROR 1" << endl;
					rv = apr_socket_create(&temp, APR_INET, SOCK_STREAM, APR_PROTO_TCP, fl->pool);
					if (rv != APR_SUCCESS)
						cout << "ERROR2" << endl;

					apr_socket_opt_set(temp, APR_SO_NONBLOCK, 1);
					apr_socket_timeout_set(temp, 0);

					rv = apr_socket_bind(temp, connectionSock);
					if (rv != APR_SUCCESS)
						cout << "ERROR 3" << endl;
					rv = apr_socket_listen(temp, SOMAXCONN);
					if (rv != APR_SUCCESS)
						cout << "ERROR 4" << endl;
					DEBUG_MSG("Becoming server\n");

					high_resolution_clock::time_point curr, start;
					start = high_resolution_clock::now();
					double timeToWait = MAX_CONNECTION_WAIT;
					bool end = false;
					while (end == false && !fl->exit)
					{
						curr = high_resolution_clock::now();
						auto durationS = duration_cast<seconds>(curr - start).count();
						if (durationS > timeToWait)
							end = true;

						apr_socket_accept(&fl->sock, temp, fl->pool);
						if (fl->sock != nullptr)
							break;
					}
					apr_socket_close(temp);
					if (fl->sock != nullptr)
					{
						apr_socket_shutdown(temp, APR_SHUTDOWN_READWRITE);
						apr_socket_opt_set(fl->sock, APR_SO_NONBLOCK, 1);
						apr_socket_timeout_set(fl->sock, 0);
						fl->connected = true;
						fl->server = true;
						fl->executing = false;
						fl->join = true;
						fl->currState = MACHINES_CONNECTED;
						//al_emit_user_event(&networkEventSource, &connectedEvent, NULL);
						eventQueue.push(connectedEvent);
						fl->error = false;
						DEBUG_MSG("Someone connected");
					}
					else
					{
						fl->error = true;
						fl->executing = false;
						fl->join = true;
						fl->errMessage = "No one connected\n";
						DEBUG_MSG("No one connected");
					}
				}

			}
			else
			{
				fl->errMessage = "Cannot create socket\n";
				fl->error = true;
				fl->executing = false;
				fl->join = true;
			}

		}
		else
		{
			fl->errMessage = "Cannot get server info\n";
			fl->error = true;
			fl->executing = false;
			fl->join = true;
		}
	}
	else
	{
		fl->errMessage = "Cannot create pool\n";
		fl->error = true;
		fl->executing = false;
		fl->join = true;
	}

}

remoteInput BurgleNetwork::getRemoteInput()
{
	remoteInput inp;
	inp.action = NO_TYPE;
	if (flags.currState != EXCHANGE_FINISHED || join() == false)
		return inp;

	if (flags.ack == true)
	{
		flags.ack = false;
		inp.action = ACK;
		DEBUG_MSG("Received a " << toString(inp.action) << " (" << inp.action << ")");
		return inp;
	}

	if (flags.error == true)
	{
		inp.action = ERRO;
		inp.errMessage = flags.errMessage;
		return inp;
	}

	vector<char> buffer(1024, 0);
	apr_size_t size = 1024;
	clock_t t = clock();
	apr_status_t rv;
	rv = apr_socket_recv(flags.sock, buffer.data(), &size);
	if (APR_STATUS_IS_EOF(rv) || size == 0 || size == 1024)
		return inp;

	packetToInput(inp, buffer);
	DEBUG_MSG("Received a " << toString(inp.action));
	if (answerInput(inp) == false)
	{
		flags.error = true;
		flags.errMessage = "Couldnt answer " + string(toString(inp.action));
	}
	
	return inp;
}
bool BurgleNetwork::answerInput(remoteInput& inp)
{
	switch (inp.action)
	{
	case MOVE:
	case PEEK:
	case PASS:
	case SPY_PATROL:
	case ADD_TOKEN:
	case USE_TOKEN:
	case CREATE_ALARM:
	case PLACE_CROW:
	case SPENT_OK:
	case INITIAL_G_POS:
	case SAFE_OPENED:
	case THROW_DICE:
	case OFFER_LOOT:
	case REQUEST_LOOT:
	case ROLL_DICE_FOR_LOOT:
		DEBUG_MSG("Sending ACK");
		return sendPacket(flags.sock, vector<char>(1, (char)ACK));
		break;

	case ERRO:
		flags.error = true;
		flags.errMessage = "Recivied error from remote player";
	default:
		return true;
	}
}
void BurgleNetwork::packetToInput(remoteInput& inp, vector<char>& pack)
{
	char n;
	int mod = 2;
	Coord temp;
	inp.action = char2action_ID(pack[0]);
	switch (char2action_ID(pack[0]))
	{
	case MOVE:
	case PEEK:
	case SPY_PATROL:
		inp.modifier = pack[5];
	case ADD_TOKEN:
	case USE_TOKEN:
	case CREATE_ALARM:
	case PLACE_CROW:
	case INITIAL_G_POS:
		inp.pos.col = pack[1] - 'A';
		inp.pos.row = pack[2] - '1';
		inp.pos.floor = pack[4] - '1';
		break;
	case SPENT_OK:
		inp.modifier = pack[1];
		break;
	case GUARD_MOVEMENT:
		n = pack[1];
		
		for (char i = 0; i < n; i++)
		{
			if (pack[2 + 4 * i+mod]==0xff)
			{
				temp.col = 0;
				temp.row = 0;
				temp.floor = 3;
				mod++;
			}
			else
			{
				temp.col = pack[mod + 4 * i];
				temp.row = pack[mod+1 + 4 * i];
				temp.floor = pack[mod+3 + 4 * i];
				
			}
			inp.guardMoves.push_back(temp);
		}
		break;
	case SAFE_OPENED:
	case OFFER_LOOT:
	case REQUEST_LOOT:
		inp.loot = (lootType)pack[1];
		break;
	case ROLL_DICE_FOR_LOOT:
		inp.modifier = pack[1]-'0';
		break;
	case THROW_DICE:
		for (int i = 1; i <= 6; i++)
		{
			if (pack[i] != '0')
				inp.dice.push_back((unsigned int)pack[i] - '0');
		}
		break;
	default:
		break;

	}
}
//Utility and bulk functions
void BurgleNetwork::coordToPacket(Coord pos, vector<char>& pack)
{
	if (pos == Coord(3, 0, 0))
	{
		pack.push_back((char)0xff);
		return;
	}
	pack.push_back(pos.col + 'A');
	pack.push_back(pos.row + '1');
	pack.push_back('F');
	pack.push_back(pos.floor + '1');
}
void BurgleNetwork::instructionWithCoord(thData* fl, action_ID act, Coord pos, char modifier)
{
	if (fl->error == true)
		return;
	threadStarter(fl);
	vector<char> pack(1, (char)act);
	coordToPacket(pos, pack);
	if (modifier != 0)
		pack.push_back(modifier);
	packetAndAck(fl, pack);
	threadCloser(fl);
	return;

}
void BurgleNetwork::instructionWithMod(thData* fl, action_ID act, char mod)
{
	if (fl->error == true)
		return;
	threadStarter(fl);
	vector<char> pack(2, (char)act);
	if (mod != 0)
		pack[1] = mod;
	else
		pack.pop_back();
	packetAndAck(fl, pack);
	threadCloser(fl);
	return;
}
void BurgleNetwork::packetAndAck(thData* fl, vector<char>& pack)
{
	action_ID act = char2action_ID(pack[0]);
	if (sendPacket(fl->sock, pack) == false)
	{
		fl->error = true;
		fl->errMessage = "Couldnt send instruction " + string(toString(act));
		return;
	}

	vector<char> buffer;
	
	if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != ACK)
	{
		fl->error = true;
		fl->errMessage = "Didnt recieve ACK for " + string(toString(act));
		return;
	}
	else fl->ack = true;
}

void BurgleNetwork::packetAndAckThreded(thData* fl, vector<char>pack)
{
	if (fl->error == true)
		return;
	threadStarter(fl);
	packetAndAck(fl, pack);
	threadCloser(fl);
	return;
}

void BurgleNetwork::sendPeek(Coord pos, char num)
{
	DEBUG_MSG("Sending PEEK");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, PEEK, pos, num);
	else
		cout << "couldn't send peek!" << endl;
}

void BurgleNetwork::sendMove(Coord pos, char num)
{
	DEBUG_MSG("Sending MOVE");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, MOVE, pos, num);
}

void BurgleNetwork::sendSpent(char yn)
{
	DEBUG_MSG("Sending SPENT_OK");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, SPENT_OK, yn);
}

void BurgleNetwork::sendAddToken(Coord pos)
{
	DEBUG_MSG("Sending ADD_TOKEN");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, ADD_TOKEN, pos, 0);
}
void BurgleNetwork::sendUseToken(Coord pos)
{
	DEBUG_MSG("Sending USE_TOKEN");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, USE_TOKEN, pos, 0);
}

void BurgleNetwork::sendThrowDice(vector <unsigned int> diceThrown)
{	DEBUG_MSG("Sending THROW_DICE");
	vector<char> pack(7, (char)THROW_DICE);
	for (unsigned int i = 0; i < diceThrown.size(); i++) 
		pack[i+1] = diceThrown[i] + '0';

	for (int i = diceThrown.size(); i < 6; i++)
		pack[i+1] = '0';

	if (join() == true)
		currThread = new thread(&BurgleNetwork::packetAndAckThreded, this, &flags, pack);

}
void BurgleNetwork::sendSafeOpened(lootType loot)
{
	DEBUG_MSG("Sending SAFE_OPENED");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, SAFE_OPENED, (char)loot);
}
void BurgleNetwork::sendCreateAlarm(Coord pos)
{
	DEBUG_MSG("Sending CREATE_ALARM");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, CREATE_ALARM, pos, 0);
}
void BurgleNetwork::sendInitialGuardPos(Coord init,Coord target)
{
	if (join() == true)
	{
		vector<char> pack(1, INITIAL_G_POS);
		coordToPacket(init, pack);
		coordToPacket(target, pack);
		sendPacket(flags.sock,pack);
	}
		
}
void BurgleNetwork::sendSpyPatrol(Coord pos, char tb)
{
	DEBUG_MSG("Sending SPY_PATROL");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, SPY_PATROL, pos, tb);
}
void BurgleNetwork::sendPlaceCrow(Coord pos)
{
	DEBUG_MSG("Sending PLACE_CROW");
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, PLACE_CROW, pos, 0);
}
void BurgleNetwork::sendOfferLoot(lootType loot)
{
	DEBUG_MSG("Sending OFFER_LOOT");
	if (join() == true)
	{
		vector<char> pack(2, (char)OFFER_LOOT);
		pack[1] = (char)loot;
		if (sendPacket(flags.sock, pack) == false)
		{
			flags.error = true;
			flags.errMessage = "Couldnt send OFFER_LOOT";
			return;
		}
	}
}
void BurgleNetwork::sendRequestLoot(lootType loot)
{
	DEBUG_MSG("Sending REQUEST_LOOT");
	if (join() == true)
	{
		vector<char> pack(2, (char)REQUEST_LOOT);
		pack[1] = (char)loot;
		if (sendPacket(flags.sock, pack) == false)
		{
			flags.error = true;
			flags.errMessage = "Couldnt send REQUEST_LOOT";
			return;
		}
	}
}
void BurgleNetwork::sendPickupLoot()
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, PICK_UP_LOOT, 0);
}
void BurgleNetwork::sendPass()
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, PASS, 0);
}
void BurgleNetwork::sendQuit()
{
	if (join() == true)
	{
		vector<char> pack(1, (char)QUIT);
		currThread = new thread(&BurgleNetwork::packetAndAckThreded, this, &flags, pack);
	}
}
void BurgleNetwork::sendError()
{
	if (join() == true)
	{
		vector<char> pack(1, (char)ERRO);
		if (sendPacket(flags.sock, pack) == false)
		{
			flags.errMessage = "Couldnt send ERROR";
			flags.error = true;
		}
	}
}
void BurgleNetwork::sendAgree()
{
	if (join() == true)
	{
		vector<char> pack(1, AGREE);
		if (sendPacket(flags.sock, pack) == false)
		{
			flags.errMessage = "Couldnt send AGREE";
			flags.error = true;
		}
	}
}
void BurgleNetwork::sendDisagree()
{
	if (join() == true)
	{
		vector<char> pack(1, DISAGREE);
		if (sendPacket(flags.sock, pack) == false)
		{
			flags.errMessage = "Couldnt send DISAGREE";
			flags.error = true;
		}
	}
}
void BurgleNetwork::sendGuardMovement(vector<Coord>& path)
{
	if (join() == true)
	{
		vector<char> pack(1, (char)GUARD_MOVEMENT);
		pack.push_back((char)path.size());
		for (auto& c : path)
			coordToPacket(c, pack);
		if (sendPacket(flags.sock, pack) == false)
		{
			flags.errMessage = "Couldnt send GUARD_MOVMENT";
			flags.error = true;
		}
	}
}
void BurgleNetwork::sendLootDice(char dice)
{
	if (join() == true)
	{
		vector<char> pack(2, ROLL_DICE_FOR_LOOT);
		pack[1] = dice + '0';
		currThread = new thread(&BurgleNetwork::packetAndAckThreded, this, &flags, pack);
	}
}
BurgleNetwork::~BurgleNetwork()
{
	apr_socket_close(flags.sock);
	apr_pool_destroy(flags.pool);
	flags.sock = nullptr;
	flags.pool = nullptr;
	apr_terminate2();
}
