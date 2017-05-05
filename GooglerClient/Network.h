#pragma once
#ifndef __NETWORK
#define __NETWORK

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")
#pragma pack( 1 )

#include <WinSock2.h>
#include <iostream>

using namespace std;

class Network
{
private:
	string mDstIp;
	WSADATA mWsaData;
	SOCKET mClientSocket;

	struct sockaddr_in mDstAddress;
	int mPort;

public:
	Network(int portNum, string dstIp);
	~Network();

	void ConnectUDP();
	void ConnectTCP();
	//int SendToDstUDP();
	int SendToDstTCP(char* buf, int bufLen);
};

#endif // !__NETWORK
