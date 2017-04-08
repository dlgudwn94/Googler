#include "ServerManager.h"

ServerManager::ServerManager(char* createFileName) {
	this->mServerIns = new Server(mRecvBuffer, BUFF_SIZE, 8888);
	this->mFileIns = new FileManage(createFileName, mRecvBuffer, BUFF_SIZE);

	mServerIns->ConnectUDP();

}

ServerManager::~ServerManager() {
	mServerIns->~Server();
	mFileIns->~FileManage();
}

void ServerManager::FileRecvStart() {
	
	while (1) {
		if (mServerIns->RecvToClient() == -1) {
			cout << "ERRER: Packet Recv Fail" << endl;
			exit(1);
		}
		if (mFileIns->WriteFile() == 0) {
			// 조건문 추가바람
		}
			
	}
}