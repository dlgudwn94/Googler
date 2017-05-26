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
	int flg;//���ϵ��丮 ����
	while (true) {
		flg = mFileIns->SetFile();//�����ϱ�
		if (flg == 0) {//���丮�ϰ��
			mFileIns->ReadyToFolderPacket();
			if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);
			count++;
			mFileIns->endData();
		}
		else if (flg == 2) {//�����ϰ��
			//file open and name send
			if (mFileIns->FileStreamOpen() == -1) exit(1);
			if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);

			while (mFileIns->ReadyToPacket() != 0) {//��������
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
			if (mNetworkIns->SendToDstTCP(mSendBuffer, BUFF_SIZE) == -1) exit(1);//�ؽ�����
			mFileIns->endData();
			cout << "����" << endl;
		}
		else {
			cout << " transmission time : " << (count * DATA_SIZE)
				<< " byte/sec" << endl;
			cout << "���۳�" << endl;
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
	int flg;//���ϵ��丮 ����
	while (true) {
		flg = mFileIns->SetFile();//�����ϱ�
		if (flg == 0) {//���丮�ϰ��
			mFileIns->ReadyToFolderPacket();
			if (mNetworkIns->SendToDstUDP(mSendBuffer, BUFF_SIZE) == -1) exit(1);
			count++;
			mFileIns->endData();
		}
		else if (flg == 2) {//�����ϰ��
							//file open and name send
			if (mFileIns->FileStreamOpen() == -1) exit(1);
			if (mNetworkIns->SendToDstUDP(mSendBuffer, BUFF_SIZE) == -1) exit(1);

			while (mFileIns->ReadyToPacket() != 0) {//��������
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
			if (mNetworkIns->SendToDstUDP(mSendBuffer, BUFF_SIZE) == -1) exit(1);//�ؽ�����
			mFileIns->endData();
			cout << "����" << endl;
		}
		else {
			cout << " transmission time : " << (count * DATA_SIZE)
				<< " byte/sec" << endl;
			cout << "���۳�" << endl;
			break;
		}
	}
}
