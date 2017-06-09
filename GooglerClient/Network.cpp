#include "Network.h"

Network::Network(int portNum, string dstIp)
{
	this->mPort = portNum;
	this->mDstIp = dstIp;
}

Network::~Network()
{
	if (shutdown(mClientSocket, SD_SEND) == SOCKET_ERROR)
		cout << "shutdown()" << endl;
	closesocket(mClientSocket);
	WSACleanup();
}

void Network::ConnectUDP()
{
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != NO_ERROR)
	{
		cerr << "ERROR: SOCKET initialization - WSAStartup" << endl;
		WSACleanup();
		exit(10);
	}

	mClientSocket = socket(PF_INET, SOCK_DGRAM, 0);

	if (mClientSocket == INVALID_SOCKET)
	{
		cerr << "ERROR: SOCKET initialization - Creating socket" << endl;
		WSACleanup();
		exit(11);
	}

	memset(&mDstAddress, 0, sizeof(mDstAddress));
	mDstAddress.sin_family = AF_INET;
	mDstAddress.sin_port = htons(mPort);
	mDstAddress.sin_addr.s_addr = inet_addr(mDstIp.c_str());
}


int Network::SendToDstUDP(char* buf, int bufLen)
{
	int error, flag;
	

	//cout << "Transmission data " << mSendBuffer << endl;

	error = sendto(mClientSocket, buf, bufLen, 0,
		(struct sockaddr*)&mDstAddress, sizeof(mDstAddress));

	if (error == -1)
		cout << "ERROR: Sendto fail" << endl;

	int addrlen = sizeof(mPeeraddr);
	flag = recvfrom(mClientSocket, mTrash, sizeof(mTrash), 0,
		(SOCKADDR*)&mPeeraddr, &addrlen);
	if (flag == -1)
		cout << "ERROR: flag fail" << endl;

	return error;
}


void Network::ConnectTCP()
{
	int error;

	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0)
	{
		cerr << "ERROR: SOCKET initialization - WSAStartup" << endl;
		WSACleanup();
		exit(10);
	}

	mClientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mClientSocket == INVALID_SOCKET)
	{
		cerr << "ERROR: SOCKET initialization - Creating socket" << endl;
		WSACleanup();
		exit(11);
	}

	memset(&mDstAddress, 0, sizeof(mDstAddress));
	mDstAddress.sin_family = AF_INET;
	mDstAddress.sin_addr.s_addr = inet_addr(mDstIp.c_str());
	mDstAddress.sin_port = htons(mPort);
	
	error = connect(mClientSocket, (SOCKADDR*)&mDstAddress, sizeof(mDstAddress));
	if (error == SOCKET_ERROR) {
		cerr << "ERROR: client Connect Fail" << endl;
		exit(14);
	}
	cout << "Connecting" << endl;
}

int Network::SendToDstTCP(char* buf, int bufLen)
{
	int error;

	//cout << "Transmission data " << mSendBuffer << endl;

	error = send(mClientSocket, buf, bufLen, 0);

	if (error == -1)
		cout << "ERROR: Send Fail" << endl;

	return error;
}