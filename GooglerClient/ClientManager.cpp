#include "ClientManager.h"

ClientManager::ClientManager(int protocal, int port)
{
	string Ip;
	string filename;
	
	cout << "Input Dst Ip: ";
	getline(cin, Ip);
	cout << "Input open file address: ";
	getline(cin, filename);

	this->mNetworkIns = new Network(port, Ip);
	this->mFileIns = new FileTransfer(filename, mSendBuffer);

	mProtocal = protocal;
}

ClientManager::~ClientManager()
{
	delete(mNetworkIns);
	delete(mFileIns);
}

void ClientManager::FileSendStart() {
	//if (mProtocal == UDP)
	//	FileSendStartUDP();
	if (mProtocal == TCP)
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
	int flg;//파일디렉토리 구분
	while (true) {
		flg = mFileIns->SetFile();//구분하기
		if (flg == 0) {//디렉토리일경우
			mFileIns->ReadyToFolderPacket();
			if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);
			count++;
		}
		else if (flg == 2) {//파일일경우
			//file open and name send
			if (mFileIns->FileStreamOpen() == -1) exit(1);
			if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);

			while (mFileIns->ReadyToPacket() != 0) {//파일전송
				if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);
				//time
				count++;
				if (GetTickCount() - t >= 1000) {
					cout << " transmission time : " << (count * DATA_SIZE)
						<< " byte/sec" << endl;
					t = GetTickCount();
					count = 0;
				}//time end
			}
			if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);//해쉬전송
			cout << "전송" << endl;
		}
		else {
			cout << " transmission time : " << (count * DATA_SIZE)
				<< " byte/sec" << endl;
			cout << "전송끝" << endl;
			break;
		}
	}
}

/*
void ClientManager::FileSendStartUDP()
{
	mNetworkIns->ConnectUDP();
	//time
	DWORD t = GetTickCount();
	int count = 1;
	//time end
	int flg;//파일디렉토리 구분
	while (true) {
		flg = mFileIns->SetFile();//구분하기
		if (flg == 0) {//디렉토리일경우
			mFileIns->ReadyToFolderPacket();
			if (mNetworkIns->SendToDstUDP() == -1) exit(1);
			count++;
		}
		else if (flg == 2) {//파일일경우
							//file open and name send
			if (mFileIns->FileStreamOpen() == -1) exit(1);
			if (mNetworkIns->SendToDstUDP() == -1) exit(1);

			while (mFileIns->ReadyToPacket() != 0) {//파일전송
				if (mNetworkIns->SendToDstUDP() == -1) exit(1);
				//time
				count++;
				if (GetTickCount() - t >= 1000) {
					cout << " transmission time : " << (count * DATA_SIZE)
						<< " byte/sec" << endl;
					t = GetTickCount();
					count = 0;
				}//time end
			}
			if (mNetworkIns->SendToDstUDP() == -1) exit(1);//해쉬전송
			cout << "전송" << endl;
		}
		else {
			cout << " transmission time : " << (count * DATA_SIZE)
				<< " byte/sec" << endl;
			cout << "전송끝" << endl;
			break;
		}
	}
}
*/