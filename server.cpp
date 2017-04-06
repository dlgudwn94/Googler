#include "server.h"

Server::Server(int port) {
	this->mPort = port;

	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != NO_ERROR)
	{
		cerr << "ERROR: SOCKET Initialization - WSAStartup" << endl;
		WSACleanup();
		exit(10);
	}

	mServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (mServerSocket == INVALID_SOCKET)
	{
		cerr << "ERROR: SOCKET Initialization - creating socket" << endl;
		WSACleanup();
		exit(11);
	}
}

Server::~Server() {
	WSACleanup();
}

void Server::ConnectUDP() {
	mAddress.sin_family = PF_INET;
	mAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	mAddress.sin_port = htons(mPort);

	// address bind
	if (bind(mServerSocket, (SOCKADDR*)&mAddress, sizeof(mAddress)) == SOCKET_ERROR)
	{
		cerr << "ERROR: ServerSocket connect fail" << endl;
		WSACleanup();
		exit(14);
	}

	// connection roof
	while (1)
	{
		mClient_addr_size = sizeof(mClient_addr);
		recvfrom(mServerSocket, mRecvBuffer, BUFFERSIZE + 1, 0,
			(struct sockaddr*)&mClient_addr, &mClient_addr_size);

		cout << mRecvBuffer << endl;

		sendto(mServerSocket, mNoticeMes.c_str(), strlen(mNoticeMes.c_str()) + 1, 0,
			(struct sockaddr*)&mClient_addr, sizeof(mClient_addr));
	}
}