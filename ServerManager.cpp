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
	if (mServerIns->RecvToClient() == -1) {//처음 패킷은 파일의 이름을 받아옴
		cout << "ERRER: Packet Recv Fail" << endl;
		exit(1);
	}
	if (mFileIns->SetFileNameFromBuf()) {//쓸 파일이 무사히 열렸는지 확인
		cout << "ERRER: Can't Create File" << endl;
		exit(1);
	}
	while (1) {
		if (mServerIns->RecvToClient() == -1) {
			cout << "ERRER: Packet Recv Fail" << endl;
			exit(1);
		}
		if (mFileIns->WriteFile() > 0) {//(0:정상, 1:종료문자열)
			cout << "File Receive Complete!" << endl;
			break;
		}
			
	}
}