#include "ServerManager.h"

ServerManager::ServerManager() {
	this->mNetworkIns = new Network(mRecvBuffer, BUFF_SIZE, 8888);
	this->mFileIns = new FileManage(mRecvBuffer);
	mNetworkIns->ConnectUDP();

}

ServerManager::~ServerManager() {
	delete(mNetworkIns);
	delete(mFileIns);
}

void ServerManager::FileRecvStart() {
	
	while (true) {
			cout << "Waitting for Recive\n";
			if (mNetworkIns->RecvToClient() == -1) {
				cout << "ERRER: Packet Recv Fail" << endl;
				exit(1);
			}
			if (mFileIns->RecvPacket()) {
				cout << "ERRER: Can't Create File" << endl;
				exit(1);
			}
	}
}