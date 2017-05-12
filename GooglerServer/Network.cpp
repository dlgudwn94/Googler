#include "Network.h"

#define LISTENQUEUESIZE 5

Network::Network(int portNum) {
	this->mPort = portNum;
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


int Network::RecvToClientUDP(char* buf, int bufLen) {
	int error;
	mClientAddrSize = sizeof(mClient_addr);

	error = recvfrom(mServerSocket, buf, bufLen, 0,
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

int Network::RecvToClientTCP(char* buf, int size) {
	int total_received;
	int received;
	
	total_received = 0;

	while (size) {
		received = recv(mClientSocketInTCP, buf, size, 0);

		if (received <= 0)
			break;

		total_received += received;
		size -= received;

		buf += received;
	}

	if (received == 0) {
		cout << "전송완료 .." << endl;
	}
	else if (received == -1) {
		cout << "ERROR: Recv Fail" << endl;
	}
	
	//receive == 0 종료 , -1 에러
	return received > 0 ? total_received : received;
}