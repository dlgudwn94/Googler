#ifndef __NETWORK
#define __NETWORK

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")

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
	char* mSendBuffer;
	int mPort;

public:
	Network(char* sendBuffer, int portNum, string dstIp);
	~Network();
	
	void ConnectUDP();
	int SendToDst();
};

#endif // !__NETWORK
