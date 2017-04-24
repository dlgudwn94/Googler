#include "ClientManager.h"

ClientManager::ClientManager(int protocal, int port)
{
	string Ip;
	string filename;
	
	cout << "Input Dst Ip: ";
	getline(cin, Ip);
	cout << "Input open file address: ";
	getline(cin, filename);

	this->mNetworkIns = new Network(mSendBuffer, BUFF_SIZE, port, Ip);
	this->mFileIns = new FileTransfer(filename, mSendBuffer);

	mProtocal = protocal;
}

ClientManager::~ClientManager()
{
	delete(mNetworkIns);
	delete(mFileIns);
}

void ClientManager::FileSendStart() {
	if (mProtocal == UDP)
		FileSendStartUDP();
	else if (mProtocal == TCP)
		FileSendStartTCP();
	else {
		cout << "ERROR: INVALID Protocal" << endl;
	}
}

void ClientManager::FileSendStartTCP()
{
	
	mNetworkIns->ConnectTCP();

	//time
	DWORD t = GetTickCount();
	int count = 1;
	//time end

	if (mFileIns->FileStreamOpen() == -1)
		exit(1);

	if (mNetworkIns->SendToDstTCP() == -1)
		exit(1);

	while (true)
	{
		//time
		if (GetTickCount() - t >= 1000) {
			cout << " transmission time : " << (count * DATA_SIZE)
				<< " byte/sec" << endl;
			t = GetTickCount();
			count = 0;
		}
		//time end

		if (mFileIns->ReadyToPacket() == 0)
		{
			
			if (mNetworkIns->SendToDstTCP() == -1)
				exit(1);

			cout << "전송완료" << endl;
			break;
		}
		
		if (mNetworkIns->SendToDstTCP() == -1)
			exit(1);
		count++;
	}
}

void ClientManager::FileSendStartUDP()
{
	mNetworkIns->ConnectUDP();

	//time
	DWORD t = GetTickCount();
	int count = 1;
	//time end

	if (mFileIns->FileStreamOpen() == -1)
		exit(1);

	// send filename
	if (mNetworkIns->SendToDstUDP() == -1)
		exit(1);

	while (true)
	{
		//time
		if (GetTickCount() - t >= 1000) {
			cout << " transmission time : " << (count * DATA_SIZE)
				<< " byte/sec" << endl;
			t = GetTickCount();
			count = 0;
		}
		//time end

		if (mFileIns->ReadyToPacket() == 0)
		{
			if (mNetworkIns->SendToDstUDP() == -1)
				exit(1);

			cout << "전송완료" << endl;
			break;
		}

		if (mNetworkIns->SendToDstUDP() == -1)
			exit(1);
		count++;
	}
}