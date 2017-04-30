#include "Network.h"

#define LISTENQUEUESIZE 5

Network::Network(char* recvBuffer, int bufSize, int portNum) {
	this->mPort = portNum;
	this->mRecvBuffer = recvBuffer;
	this->mBuffSize = bufSize;
	mClientAddrSize = 0;
	mAddressSize = 0;
}

Network::~Network() {
	if (mClientSocketInTCP != INVALID_SOCKET)
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
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0)
	{
		cerr << "ERROR: SOCKET Initialization - WSAStartup" << endl;
		WSACleanup();
		exit(10);
	}

	mServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mServerSocket == INVALID_SOCKET)
	{
		cerr << "ERROR: SOCKET Initialization - creating socket" << endl;
		WSACleanup();
		exit(11);
	}

	memset(&mAddress, 0, sizeof(mAddress));
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	mAddress.sin_port = htons(mPort);
	
	if (bind(mServerSocket, (SOCKADDR*)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		cerr << "ERROR: ServerSocket connect fail" << endl;
		WSACleanup();
		exit(14);
	}
	cout << "bind clear" << endl;

	if (listen(mServerSocket, LISTENQUEUESIZE) == -1) {
		cerr << "ERROR: ServerSocket listen fail" << endl;
		WSACleanup();
		exit(14);
	}
	cout << "listen clear" << endl;

	
	mAddressSize = sizeof(mAddress);
	cout << "Waiting Connect from client" << endl;
}

bool Network::AcceptTCP() {
	mClientAddrSize = sizeof(mClient_addr);
	mClientSocketInTCP = accept(mServerSocket, (SOCKADDR*)&mClient_addr, &mClientAddrSize);
	if (mClientSocketInTCP == INVALID_SOCKET) {
		cerr << "ERROR: Client Socket accept fail" << endl;
		return false;
	}
	cout << "접속 IP : " << inet_ntoa(mClient_addr.sin_addr) << endl;
	return true;
}

int Network::RecvToClientTCP() {
	int error;

	error = recv(mClientSocketInTCP, mRecvBuffer, mBuffSize, 0);
	cout << "recv packet" << endl;
	if (error == 0) {
		cout << "전송 완료.." << endl;
	}
	if (error == -1)
		cout << "ERROR: recv Fail" << endl;

	//CloseHandle(CreateThread(0, 0, Print, (void*)mClientSocketInTCP, 0, 0));
	//cout << mRecvBuffer << endl;

	return error;
}