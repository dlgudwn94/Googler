#include "ClientManager.h"

ClientManager::ClientManager()
{
	string Ip;
	string filename;
	
	cout << "Input Dst Ip: ";
	getline(cin, Ip);
	cout << "Input open file address: ";
	getline(cin, filename);

	this->mNetworkIns = new Network(mSendBuffer, 8888, Ip);
	this->mFileIns = new FileTransfer(filename, mSendBuffer);

	mNetworkIns->ConnectUDP();

	if (mFileIns->FileStreamOpen() == -1)
		exit(1);

	// send filename
	if (mNetworkIns->SendToDst() == -1)
		exit(1);
}

ClientManager::~ClientManager()
{
	delete(mNetworkIns);
	delete(mFileIns);
}

void ClientManager::FileSendStart()
{
	while (true)
	{
		if (mFileIns->ReadyToPacket() == 0)
		{
			if (mNetworkIns->SendToDst() == -1)
				exit(1);

			cout << "전송완료" << endl;
			break;
		}
		
		if (mNetworkIns->SendToDst() == -1)
			exit(1);
	}
}