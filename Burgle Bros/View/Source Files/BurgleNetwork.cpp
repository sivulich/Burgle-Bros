#include "../Header Files/BurgleNetwork.h"



BurgleNetwork::BurgleNetwork(string IP)
{
	flags.currState = WAITINNG_CONN;
	flags.exit = false;
	flags.error = false;
	apr_initialize();
	currThread = new thread(&BurgleNetwork::establishConn,this,&flags , IP);	
}

bool
BurgleNetwork::join()
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
void
BurgleNetwork::threadStarter(thData* fl)
{
	fl->executing = true;
}
void
BurgleNetwork::threadCloser(thData* fl)
{
	fl->executing = false;
	fl->join = true;
}
bool
BurgleNetwork::sendPacket(apr_socket_t* sock,const vector<char>& dat)
{
	apr_size_t size = dat.size();
	apr_status_t rv;
	if (dat.size() == 0)
		return true;
	rv=apr_socket_send(sock, dat.data(), &size);
	if (rv == APR_SUCCESS)
		return true;
	else return false;
}
bool
BurgleNetwork::recievePacket(apr_socket_t* sock, vector<char>& dat)
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
	dat.insert(dat.end(), buffer.begin(), buffer.begin()+size);
	return true;
}

void 
BurgleNetwork::exchangeNames(thData* fl, const string& name)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);
	/*First contact server sends NAME, client listens*/
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
		if (recievePacket(fl->sock,buffer)==false || buffer.size() != 1 || buffer[0]!=NAME)
		{
			fl->error = true;
			fl->join = true;
			fl->executing = false;
			fl->errMessage = "Didnt recieve first packet";
			return;
		}
		
	}
	this_thread::sleep_for(chrono::milliseconds(10));
	/*Second packet Client sends NAME_IS, server listens*/
	if (fl->server == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock,buffer)==false || buffer.size()==0 || buffer[0] != NAME_IS)
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
		vector<char> pack(2+name.size());
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
	/*Third packet Server sends ACK, client listens*/
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
	/*Fourth packet client sends NAME, server listens*/
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
	/*Fifth packet server sends NAME_IS, client listens*/
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
	/*Sixth packet client sends ACK,server listens*/
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
void 
BurgleNetwork::exchangeCharacters(thData* fl, const characterType type)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	/*First packet server sends I_AM, client listens*/
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
		fl->remotePlayer =(characterType) buffer[1];
	}
	this_thread::sleep_for(chrono::milliseconds(10));

	/*Second packet server listens, client sends I_AM*/
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
void
BurgleNetwork::exchangeGuard(thData* fl, const Coord guardPos, Coord guardTarget)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	/*First packet server sends INITIAL_G_POS, client listens*/
	if (fl->server == true)
	{
		vector<char> pack(9);
		pack[0] = INITIAL_G_POS;
		pack[1] = guardPos.col+'A';
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
		fl->remoteGuardPos.col=buffer[1] - 'A';
		fl->remoteGuardPos.row = buffer[2] - '1';
		fl->remoteGuardPos.col = buffer[4] -'1';
		fl->remoteGuardTarget.col = buffer[5] - 'A';
		fl->remoteGuardTarget.row = buffer[6] - '1';
		fl->remoteGuardTarget.col = buffer[8] - '1';
	}
	this_thread::sleep_for(chrono::milliseconds(10));

	/*Second packet server listens, client sends ACK*/
	if (fl->server == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] !=ACK)
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
void
BurgleNetwork::exchangeBoard(thData* fl, Board& board, const Coord playerPos)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	/*First packet server sends INITIAL_G_POS, client listens*/
	if (fl->server == true)
	{
		vector<char> pack(1);
		pack[0] = START_INFO;
		for (size_t f = 0; f < 3; f++)
		{
			for (size_t r = 0; r < 4; r++)
			{
				for (size_t c = 0; c < 4; c++)
				{
					pack.push_back((char)(board[f][r][c]->getType()));
				}
			}
		}
		pack.push_back((char)(playerPos.col + 'A'));
		pack.push_back((char)(playerPos.row + '1'));
		pack.push_back('F');
		pack.push_back((char)(playerPos.floor + '1'));
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
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 53 || buffer[0] != START_INFO)
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
	}

	/*Second packet server listens, client sends ACK*/
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
void
BurgleNetwork::exchangeFirst(thData* fl)
{
	if (fl->error == true)
	{
		fl->join = true;
		return;
	}
	threadStarter(fl);

	/*First packet server sends I_START/YOU_START , client listens*/
	if (fl->server == true)
	{
		vector<char> pack(1);
		fl->iStart = (bool)(rand() % 2);
		pack[0] = (fl->iStart==true ? I_START:YOU_START);
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
	/*If server starts, client sends ACK, server listens*/
	if (fl->server == true && fl->iStart == true)
	{
		vector<char> buffer;
		if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || buffer[0] != ACK )
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
bool
BurgleNetwork::startupPhase(const string& name, const characterType type, const Coord guardPos, const Coord guardTarget,  Board& board,const Coord playerPos)
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
		cout << "Name exchange succesfull I am "<<name<< ". Remote Name: " << flags.remoteName << endl;
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
		currThread = new thread(&BurgleNetwork::exchangeBoard, this, &flags, board,playerPos);
	}
	else if (flags.currState == EXCHANGE_BOARD)
	{
		if (!join())
			return false;
		cout << "Board exchange succesfull" << endl;
		flags.currState = EXCHANGE_FIRST;
		currThread = new thread(&BurgleNetwork::exchangeFirst, this, &flags);
	}
	else if (flags.currState==EXCHANGE_FIRST)
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
	
void
BurgleNetwork::establishConn(thData* fl, string IP)
{
	if (fl->error == true)
		return;
	fl->error = false;
	fl->executing = true;
	fl->join = false;
	apr_status_t rv;
	apr_sockaddr_t * connectionSock;
	rv=apr_pool_create(&(fl->pool), NULL);
	if (rv == APR_SUCCESS)
	{
		rv = apr_sockaddr_info_get(&connectionSock, IP.c_str(), APR_UNSPEC, PORT, 0, fl->pool);
		if (rv == APR_SUCCESS)
		{
			rv = apr_socket_create(&fl->sock, APR_UNSPEC, SOCK_STREAM, APR_PROTO_TCP, fl->pool); //cambiar UNSPEC por APR_INET
			if (rv == APR_SUCCESS)
			{
				apr_socket_opt_set(fl->sock, APR_SO_NONBLOCK, 1);
				apr_socket_timeout_set(fl->sock, DEF_SOCK_TIMEOUT);
				int timeToWait = 200 + rand() % 9800;
				clock_t t = clock();
				printf("Trying to connect as client\n");
				while (int(double(clock() - t) / double(CLOCKS_PER_SEC / 1000)) < timeToWait)
				{
					rv = apr_socket_connect(fl->sock, connectionSock);
					if (rv == APR_SUCCESS)
						break;
				}
				if (rv == APR_SUCCESS)
				{
					fl->server = false;
					fl->executing = false;
					fl->join = true;
					fl->error = false;
					fl->currState = MACHINES_CONNECTED;
				}
				else
				{
					t = clock();
					apr_socket_t* temp;
					fl->sock = nullptr;
					apr_sockaddr_info_get(&connectionSock,nullptr, APR_UNSPEC, PORT, 0, fl->pool);
					apr_socket_create(&temp, APR_UNSPEC, SOCK_STREAM, APR_PROTO_TCP, fl->pool);
					apr_socket_opt_set(temp, APR_SO_NONBLOCK, 1);

					apr_socket_timeout_set(temp, 0);

					apr_socket_opt_set(temp, APR_SO_REUSEADDR, 1);
					apr_socket_bind(temp, connectionSock);
					apr_socket_listen(temp, SOMAXCONN);
					printf("Becoming server\n");
					while (((clock() - t) / CLOCKS_PER_SEC < MAX_CONNECTION_WAIT) && !fl->exit)
					{
						apr_socket_accept(&fl->sock, temp, fl->pool);
						if (fl->sock != nullptr)
							break;
					}
					apr_socket_close(temp);
					if (fl->sock != nullptr)
					{
						fl->server = true;
						fl->executing = false;
						fl->join = true;
						fl->currState = MACHINES_CONNECTED;
						fl->error = false;
					}
					else
					{
						fl->error = true;
						fl->executing = false;
						fl->join = true;
						fl->errMessage = "No one connected\n";
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

/*Utility and bulk functions*/
void BurgleNetwork::coordToPacket(Coord pos, vector<char>& pack)
{
	pack.push_back( pos.col + 'A');
	pack.push_back( pos.row + '1');
	pack.push_back( 'F');
	pack.push_back( pos.floor + '1');
}
void BurgleNetwork::instructionWithCoord(thData* fl,action_ID act, Coord pos, char modifier)
{
	if (fl->error = true)
		return;
	threadStarter(fl);
	vector<char> pack(1,(char)act);
	coordToPacket(pos, pack);
	if (modifier != 0)
		pack.push_back(modifier);
	packetAndAck(fl, pack);
	threadCloser(fl);
	return;
	
}
void BurgleNetwork::instructionWithMod(thData* fl, action_ID act, char mod, char* ans)
{
	if (fl->error = true)
		return;
	threadStarter(fl);
	vector<char> pack(2, (char)act);
	if (mod != 0)
		pack[1] = mod;
	else
		pack.pop_back();
	if (ans == nullptr)
		packetAndAck(fl, pack);
	else
		packetAndAD(fl, pack, ans);
	threadCloser();
	return;
}
void BurgleNetwork::packetAndAD(thData* fl, vector<char>& pack, char* ans)
{
	action_ID act = (action_ID)pack[0];
	if (sendPacket(fl->sock, pack) == false)
	{
		fl->error = true;
		fl->errMessage = "Couldnt send instruction " + string(toString(act));
		return;
	}

	vector<char> buffer;
	if (recievePacket(fl->sock, buffer) == false || buffer.size() != 1 || (buffer[0] != AGREE && buffer[0]!=DISAGREE ))
	{
		fl->error = true;
		fl->errMessage = "Didnt recieve AGREE/DISAGREE for " + string(toString(act));
		return;
	}
	*ans = buffer[0];
}
void BurgleNetwork::packetAndAck(thData* fl,vector<char>& pack)
{
	action_ID act = (action_ID)pack[0];
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
}
void BurgleNetwork::packetAndAckThreded(thData* fl, vector<char>pack)
{
	if (fl->error = true)
		return;
	threadStarter(fl);
	packetAndAck(fl, pack);
	threadCloser(fl);
	return;
}
void BurgleNetwork::sendPeek(Coord pos, char num)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this,&flags, PEEK, pos, num));
}
void BurgleNetwork::sendMove(Coord pos, char num)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, MOVE, pos, num));
}
void BurgleNetwork::sendSpent(char yn)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, SPENT_OK,yn));
}
void BurgleNetwork::sendAddToken(Coord pos)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, ADD_TOKEN, pos));
}
void BurgleNetwork::sendUseToken(Coord pos)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, USE_TOKEN, pos));
}
void BurgleNetwork::sendThrowDice(char d1, char d2, char d3, char d4, char d5, char d6)
{
	vector<char> pack(7, (char)THROW_DICE);
	pack[1] = d1;
	pack[2] = d2;
	pack[3] = d3;
	pack[4] = d4;
	pack[5] = d5;
	pack[6] = d6;
	if (join() == true)
		currThread = new thread(&BurgleNetwork::packetAndAckThreded, this, &flags, pack);
	return;

}
void BurgleNetwork::sendSafeOpened(lootType loot)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionMod, this, &flags, SAFE_OPENED, (char)loot));
}
void BurgleNetwork::sendCreateAlarm(Coord pos)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, CREATE_ALARM, pos));
}
void BurgleNetwork::sendSpyPatrol(Coord pos, char tb)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, SPY_PATROL, pos, tb));
}
void BurgleNetwork::sendPlaceCrow(Coord pos)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithCoord, this, &flags, PLACE_CROW, pos));
}
void BurgleNetwork::sendOfferLoot(lootType loot, char*ans)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags,OFFER_LOOT, (char)loot,ans));
}
void BurgleNetwork::sendRequestLoot(lootType loot, char*ans)
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, REQUEST_LOOT, (char)loot, ans));
}
void BurgleNetwork::sendPickupLoot()
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, PICK_UP_LOOT);
}
void BurgleNetwork::sendPass()
{
	if (join() == true)
		currThread = new thread(&BurgleNetwork::instructionWithMod, this, &flags, PASS));
}
void BurgleNetwork::sendQuit()
{
	if (join() == true)
	{
		vector<char> pack(1, QUIT);
		currThread = new thread(&BurgleNetwork::packetAndAckThreded, this, &flags, pack);
	}
}
void BurgleNetwork::sendError()
{
	if (join() == true)
	{
		vector<char> pack(1, ERROR);
		sendPacket(flags.sock, pack);
	}
}
void BurgleNetwork::sendAgree()
{
	if (join() == true)
	{
		vector<char> pack(1, AGREE);
		sendPacket(flags.sock, pack);
	}
}
void BurgleNetwork::sendDisagree()
{
	if (join() == true)
	{
		vector<char> pack(1, DISAGREE);
		sendPacket(flags.sock, pack);
	}
}
void BurgleNetwork::sendGuardMovement(vector<Coord>& path)
{
	if (join() == true)
	{
		vector<char> pack(1, GUARD_MOVEMENT);
		for (auto& c : path)
			coordToPacket(c, pack);
		sendPacket(flags.sock, pack);
	}
}
void BurgleNetwork::sendLootDice(char dice)
{
	if (join() == true)
	{
		vector<char> pack(2, ROLL_DICE_FOR_LOOT);
		pack[1] = dice;
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
