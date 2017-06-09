
#ifndef __NETWORK
#define __NETWORK

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")
#pragma pack( 1 )

#include <WinSock2.h>
#include <iostream>
#include "IpCheck.h"

using namespace std;

class Network {
private:
	int mPort;
	WSADATA mWsaData;
	SOCKET mServerSocket;
	SOCKET mClientSocketInTCP;
	
	struct sockaddr_in mAddress;
	struct sockaddr_in mClient_addr;
	int mClientAddrSize;
	int mAddressSize;

	IpCheck mIpCheck;

public:
	Network(int portNum);
	~Network();
	void ConnectUDP();
	void ConnectTCP();
	bool AcceptTCP();
	int RecvToClientUDP(char* buf, int bufLen);
	int RecvToClientTCP(char* buf, int bufLen);
};

#endif // !__NETWORK
