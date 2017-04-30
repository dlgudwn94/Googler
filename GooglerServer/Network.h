
#ifndef __NETWORK
#define __NETWORK

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")
#pragma pack( 1 )

#include <WinSock2.h>
#include <iostream>

using namespace std;

class Network {
private:
	char* mRecvBuffer;

	int mPort;
	WSADATA mWsaData;
	SOCKET mServerSocket;
	SOCKET mClientSocketInTCP;
	int mBuffSize;
	struct sockaddr_in mAddress;
	struct sockaddr_in mClient_addr;
	int mClientAddrSize;
	int mAddressSize;

public:
	Network(char* recvBuffer, int bufSize, int portNum);
	~Network();
	void ConnectUDP();
	void ConnectTCP();
	bool AcceptTCP();
	int RecvToClientUDP();
	int RecvToClientTCP();
};

#endif // !__NETWORK
