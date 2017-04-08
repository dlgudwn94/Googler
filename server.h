#pragma once

#ifndef __UDPSERVER
#define __UDPSERVER

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <iostream>

using namespace std;

class Server {
private:
	//DATA stream side
	//char mSendBuffer[BUFFERSIZE + 1];
	char* mRecvBuffer;
	int mBuf_size;


	
	

	//Network Variable
	int mPort;

	string mNoticeMes = "SERVER READY";
	WSADATA mWsaData;
	SOCKET mServerSocket;
	struct sockaddr_in mAddress;
	struct sockaddr_in mClient_addr;
	int mClient_addr_size;

public:
	Server(char* buffer, int BUFF_SIZE, int port);
	~Server();
	void ConnectUDP();
	int RecvToClient();
};



#endif // !__UDPSERVER
