#include <winsock.h>
#include <iostream>
#include "ClientManager.h"
using namespace std;

#ifndef __UDPCLIENT
#define __UDPCLIENT

#pragma comment (lib, "Ws2_32.lib")

class Network
{
private:
	int sock;
	int pNum;
	WSADATA wsaData;
	struct sockaddr_in sin;
	int mBuf_size;

public:

	Network(int port);
	~Network();


};

#endif 