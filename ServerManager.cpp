#include "ServerManager.h"

ServerManager::ServerManager() {
	this->mNetworkIns = new Network(mRecvBuffer, BUFF_SIZE, 8888);
	this->mFileIns = new FileManage(mRecvBuffer);
	
	mNetworkIns->ConnectUDP();

	//recv Filename
	if (mNetworkIns->RecvToClient() == -1)
		exit(1);

	
	int error = mFileIns->FileStreamOpen();
	if (error == -2 || error == -1)
		exit(1);

}

ServerManager::~ServerManager() {
	delete(mNetworkIns);
	delete(mFileIns);
}

void ServerManager::FileRecvStart() {
	
	while (true) {
		if (mNetworkIns->RecvToClient() == -1)
			exit(1);

		cout << "Packet Count : " << mPacketCount << endl;
		mPacketCount++;
		if (mFileIns->UnpackPacket() == 0) {
			cout << "전송완료" << endl;
			break;
		}
	}
}