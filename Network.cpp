#include "Network.h"

Network::Network(char* sendBuffer, int portNum, string dstIp)
{
	this->mPort = portNum;
	this->mSendBuffer = sendBuffer;
	this->mDstIp = dstIp;

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
}

Network::~Network()
{
	WSACleanup();
}

void Network::ConnectUDP()
{
	memset(&mDstAddress, 0, sizeof(mDstAddress));
	mDstAddress.sin_family = AF_INET;
	mDstAddress.sin_port = htons(mPort);
	mDstAddress.sin_addr.s_addr = inet_addr(mDstIp.c_str());
}

int Network::SendToDst()
{
	int error;
	
	cout << "Transmission data " << mSendBuffer << endl;
	
	error = sendto(mClientSocket, mSendBuffer, 1024, 0,
		(struct sockaddr*)&mDstAddress, sizeof(mDstAddress));

	if (error == -1)
		cout << "ERROR: Sendto fail" << endl;
	
	return error;
}