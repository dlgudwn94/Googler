#include "ServerManager.h"

ServerManager::ServerManager() {
	this->mServerIns = new Server(mRecvBuffer, BUFF_SIZE, 8888);
	this->mFileIns = new FileManage(mRecvBuffer, BUFF_SIZE);
	mServerIns->ConnectUDP();

}

ServerManager::~ServerManager() {
	mServerIns->~Server();
	mFileIns->~FileManage();
}

void ServerManager::FileRecvStart() {
	
	while (1) {
			cout << "Waitting for Recive\n";
			if (mServerIns->RecvToClient() == -1) {
				cout << "ERRER: Packet Recv Fail" << endl;
				exit(1);
			}
			if (mFileIns->RecvPacket()) {
				cout << "ERRER: Can't Create File" << endl;
				exit(1);
			}
	}
}