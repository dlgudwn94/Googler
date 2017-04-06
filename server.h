#pragma once

#ifndef __UDPSERVER
#define __UDPSERVER

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")

#include <iostream>
#include <WinSock2.h>

#define BUFFERSIZE (512)

using namespace std;

class Server {
private:
	//DATA stream side
	char mSendBuffer[BUFFERSIZE + 1];
	char mRecvBuffer[BUFFERSIZE + 1];


	
	

	//Network Variable
	int mPort;

	string mNoticeMes = "SERVER READY";
	WSADATA mWsaData;
	SOCKET mServerSocket;
	struct sockaddr_in mAddress;
	struct sockaddr_in mClient_addr;
	int mClient_addr_size;

public:
	Server(int port);
	~Server();
	void ConnectUDP();

};



#endif // !__UDPSERVER
