#include "ClientManager.h"

ClientManager::ClientManager()
{
	string Ip;
	string filename;
	
	cout << "Input Dst Ip: ";
	getline(cin, Ip);
	cout << "Input open file address: ";
	getline(cin, filename);

	this->mNetworkIns = new Network(mSendBuffer, BUFF_SIZE, 8888, Ip);
	this->mFileIns = new FileTransfer(filename, mSendBuffer);

	//mNetworkIns->ConnectUDP();
	mNetworkIns->ConnectTCP();

	if (mFileIns->FileStreamOpen() == -1)
		exit(1);

	// send filename
	//if (mNetworkIns->SendToDstUDP() == -1)
	//	exit(1);
	if (mNetworkIns->SendToDstTCP() == -1)
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
			//if (mNetworkIns->SendToDstUDP() == -1)
			//	exit(1);
			if (mNetworkIns->SendToDstTCP() == -1)
				exit(1);

			cout << "전송완료" << endl;
			break;
		}
		
		//if (mNetworkIns->SendToDstUDP() == -1)
		//	exit(1);
		if (mNetworkIns->SendToDstTCP() == -1)
			exit(1);
	}
}