#include "ClientManager.h"
#include <fstream>

ClientManager::ClientManager()
{
	string Ip;
	string filename;
	if (this->mFileIns->isRet(&Ip, &filename)) {
		cout << "\nResume found ( ip : "<<Ip<<" , filename : "<<filename<<" )\n\n";
	}
	else {
		cout << "Input Dst Ip: ";
		getline(cin, Ip);
		cout << "Input open file address: ";
		getline(cin, filename);
	}
	mIp = Ip;
	
	this->mFileIns = new FileTransfer(filename, mSendBuffer,Ip);

	
}

ClientManager::~ClientManager()
{
	delete(mNetworkIns);
	//delete(mFileIns);
	mFileIns->closeData();
}

void ClientManager::FileSendStart() {

	// file Size check
	if (mFileIns->FileSize() < 1024 * 64)
		mProtocal = UDP;
	else
		mProtocal = TCP;

	

	if (mProtocal == UDP) {
		this->mNetworkIns = new Network(8888, mIp);
		FileSendStartUDP();
	}
	else if (mProtocal == TCP) {
		this->mNetworkIns = new Network(9999, mIp);
		FileSendStartTCP();
	}	
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
			mFileIns->endData();
		}
		else if (flg == 2) {//파일일경우
			//file open and name send
			if (mFileIns->FileStreamOpen() == -1) exit(1);
			if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);

			while (mFileIns->ReadyToPacket() != 0) {//파일전송
				if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);
				mFileIns->setData();
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
			mFileIns->endData();
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
			if (mNetworkIns->SendToDstUDP(mSendBuffer, BUFF_SIZE) == -1) exit(1);
			count++;
			mFileIns->endData();
		}
		else if (flg == 2) {//파일일경우
							//file open and name send
			if (mFileIns->FileStreamOpen() == -1) exit(1);
			if (mNetworkIns->SendToDstUDP(mSendBuffer, BUFF_SIZE) == -1) exit(1);

			while (mFileIns->ReadyToPacket() != 0) {//파일전송
				if (mNetworkIns->SendToDstUDP(mSendBuffer, BUFF_SIZE) == -1) exit(1);
				mFileIns->setData();
				//time
				count++;
				if (GetTickCount() - t >= 1000) {
					cout << " transmission time : " << (count * DATA_SIZE)
						<< " byte/sec" << endl;
					t = GetTickCount();
					count = 0;
				}//time end
			}
			if (mNetworkIns->SendToDstUDP(mSendBuffer, BUFF_SIZE) == -1) exit(1);//해쉬전송
			mFileIns->endData();
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
