#include "Network.h"

Network::Network(char* recvBuffer, int bufSize, int portNum) {
	this->mPort = portNum;
	this->mRecvBuffer = recvBuffer;
	this->mBuffSize = bufSize;

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
}

Network::~Network() {
	WSACleanup();
}

void Network::ConnectUDP() {
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

int Network::RecvToClient() {
	int error;
	mClientAddrSize = sizeof(mClient_addr);

	error = recvfrom(mServerSocket, mRecvBuffer, mBuffSize + 1, 0,
		(struct sockaddr*)&mClient_addr, &mClientAddrSize);

	cout << "Recv : " << mRecvBuffer << endl;

	if (error == -1)
		cout << "ERROR: recvfrom Fail" << endl;

	return error;
}