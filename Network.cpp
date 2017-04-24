#include "Network.h"

#define LISTENQUEUESIZE 5

Network::Network(char* recvBuffer, int bufSize, int portNum) {
	this->mPort = portNum;
	this->mRecvBuffer = recvBuffer;
	this->mBuffSize = bufSize;

	
}

Network::~Network() {
	if(mClientSocketInTCP != INVALID_SOCKET)
		closesocket(mClientSocketInTCP);
	closesocket(mServerSocket);
	WSACleanup();
}

void Network::ConnectUDP() {
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != NO_ERROR)
	{
		cerr << "ERROR: SOCKET Initialization - WSAStartup" << endl;
		WSACleanup();
		exit(10);
	}

	mServerSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (mServerSocket == INVALID_SOCKET)
	{
		cerr << "ERROR: SOCKET Initialization - creating socket" << endl;
		WSACleanup();
		exit(11);
	}

	mAddress.sin_family = AF_INET;
	mAddress.sin_port = htons(mPort);
	mAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	// socket bind
	if (bind(mServerSocket, (SOCKADDR*)&mAddress, sizeof(mAddress)) == SOCKET_ERROR)
	{
		cerr << "ERROR: ServerSocket connect fail" << endl;
		WSACleanup();
		exit(14);
	}
}

int Network::RecvToClientUDP() {
	int error;
	mClientAddrSize = sizeof(mClient_addr);

	error = recvfrom(mServerSocket, mRecvBuffer, mBuffSize, 0,
		(struct sockaddr*)&mClient_addr, &mClientAddrSize);


	if (error == -1)
		cout << "ERROR: recvfrom Fail" << endl;

	return error;
}

void Network::ConnectTCP() {
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != NO_ERROR)
	{
		cerr << "ERROR: SOCKET Initialization - WSAStartup" << endl;
		WSACleanup();
		exit(10);
	}

	mServerSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (mServerSocket == INVALID_SOCKET)
	{
		cerr << "ERROR: SOCKET Initialization - creating socket" << endl;
		WSACleanup();
		exit(11);
	}


	mAddress.sin_family = AF_INET;
	mAddress.sin_port = htons(mPort);
	mAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(mServerSocket, (SOCKADDR*)&mAddress, sizeof(mAddress)) == SOCKET_ERROR) {
		cerr << "ERROR: ServerSocket connect fail" << endl;
		WSACleanup();
		exit(14);
	}

	if (listen(mServerSocket, LISTENQUEUESIZE) == SOCKET_ERROR) {
		cerr << "ERROR: ServerSocket listen fail" << endl;
		WSACleanup();
		exit(14);
	}

	mClientAddrSize = sizeof(mClient_addr);
	
}

bool Network::AcceptTCP() {
	mClientSocketInTCP = accept(mServerSocket, (SOCKADDR*)&mClient_addr, &mClientAddrSize);
	if (mClientSocketInTCP == INVALID_SOCKET) {
		cerr << "ERROR: Client Socket accept fail" << endl;
		return false;
	}
	return true;
}

int Network::RecvToClientTCP() {
	int error;
	
	error = recv(mClientSocketInTCP, mRecvBuffer, mBuffSize, 0);

	if (error == 0)
		AcceptTCP();
	if (error == -1)
		cout << "ERROR: recv Fail" << endl;

	return error;
}