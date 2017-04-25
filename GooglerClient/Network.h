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
	int mBufferSize;
	int mPort;

public:
	Network(char* sendBuffer, int buffSize, int portNum, string dstIp);
	~Network();
	
	void ConnectUDP();
	void ConnectTCP();
	int SendToDstUDP();
	int SendToDstTCP();
};

#endif // !__NETWORK
