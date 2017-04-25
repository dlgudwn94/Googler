#include "Network.h"

Network::Network(char* sendBuffer, int buffSize, int portNum, string dstIp)
{
	this->mPort = portNum;
	this->mSendBuffer = sendBuffer;
	this->mDstIp = dstIp;
	this->mBufferSize = buffSize;


}

Network::~Network()
{
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

int Network::SendToDstUDP()
{
	int error;
	
	//cout << "Transmission data " << mSendBuffer << endl;
	
	error = sendto(mClientSocket, mSendBuffer, mBufferSize, 0,
		(struct sockaddr*)&mDstAddress, sizeof(mDstAddress));

	if (error == -1)
		cout << "ERROR: Sendto fail" << endl;
	
	return error;
}

void Network::ConnectTCP()
{
	int error;

	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != NO_ERROR)
	{
		cerr << "ERROR: SOCKET initialization - WSAStartup" << endl;
		WSACleanup();
		exit(10);
	}

	mClientSocket = socket(PF_INET, SOCK_STREAM, 0);

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

	error = connect(mClientSocket, (SOCKADDR*)&mDstAddress, sizeof(mDstAddress));
	if (error == SOCKET_ERROR) {
		cerr << "ERROR: client Connect Fail" << endl;
		exit(14);
	}
}

int Network::SendToDstTCP()
{
	int error;

	//cout << "Transmission data " << mSendBuffer << endl;

	error = send(mClientSocket, mSendBuffer, mBufferSize, 0);

	if (error == -1)
		cout << "ERROR: Send Fail" << endl;

	return error;
}