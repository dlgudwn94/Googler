#include "Network.h"

Network::Network(int port)
{
	this->pNum = port;
	this->mBuf_size = BUFF_SIZE;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		cerr << "WSAStartup() failed" << endl; 
		WSACleanup();
		exit(1);
	}

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		cerr << "socket() failed" << endl;
		WSACleanup();
		exit(1);
	}
}

Network::~Network() {
	WSACleanup();
}
