#include "ServerManager.h"

ServerManager::ServerManager() {
	this->mServerIns = new Server(mRecvBuffer, BUFF_SIZE, 8888);
	this->mFileIns = new FileManage(mRecvBuffer, BUFF_SIZE);
	RecvFlg = 0;
	mServerIns->ConnectUDP();

}

ServerManager::~ServerManager() {
	mServerIns->~Server();
	mFileIns->~FileManage();
}

void ServerManager::FileRecvStart() {
	
	while (1) {
		if (RecvFlg == 0) {
			if (mServerIns->RecvToClient() == -1) {//처음 패킷은 파일의 이름을 받아옴
				cout << "ERRER: Packet Recv Fail" << endl;
				exit(1);
			}
			if (mFileIns->SetFileNameFromBuf()) {//쓸 파일이 무사히 열렸는지 확인
				cout << "ERRER: Can't Create File" << endl;
				exit(1);
			}
			RecvFlg = 1;
		}
		else {
			if (mServerIns->RecvToClient() == -1) {
				cout << "ERRER: Packet Recv Fail" << endl;
				exit(1);
			}
			if (mFileIns->WriteFile() > 0) {//(0:정상, 1:종료문자열)
				cout << "File Receive Complete!" << endl;
				RecvFlg = 0; //파일수신 완료, 파일이름 받는상태로
			}
		}
			
	}
}